import io
import sys
import os
from ftplib import FTP, error_perm, error_reply, _GLOBAL_DEFAULT_TIMEOUT
from mycrypto import MyCipher
from cryptography.exceptions import InvalidSignature

ip = 'localhost'


class MyFTPClient(FTP):
    """
    The custom FTP client object, extending the FTP object from the builtin ftplib library.
    This class overrides server-interaction methods in order to handle encryption/decryption on the client side.
    The changes and additions are detailed in all relevant methods below.
    The encryption operations themselves are managed by a MyCipher object, defined in mycrypto.py.
    """

    def __init__(self, host='', user='', passwd='', acct='', timeout=_GLOBAL_DEFAULT_TIMEOUT, source_address=None):
        self._cipher = None
        super().__init__(host, user, passwd, acct, timeout, source_address)

    def _encrypt_filename(self, filename):
        return self._cipher.encrypt(filename.encode(), is_filename=True).hex()

    def _decrypt_filename(self, filename):
        try:
            return self._cipher.decrypt(bytes.fromhex(filename)).decode()
        except InvalidSignature:
            print('The filename has been altered!', file=sys.stderr)
            return filename

    @staticmethod
    def _is_regular_filename(filename):
        return not (not filename or filename in ('.', '..'))

    def _encrypt_path(self, path):
        return '/'.join([self._encrypt_filename(dirname) if self._is_regular_filename(dirname) else dirname
                         for dirname in path.split('/')])

    def _decrypt_path(self, path):
        if path.startswith('"'):
            return '"%s"' % self._decrypt_path(path[1:-1])
        if path.endswith(',') or path.endswith('.'):
            return "%s%s" % (self._decrypt_path(path[:-1]), path[-1])
        return '/'.join([self._decrypt_filename(dirname) if self._is_regular_filename(dirname) and len(dirname) >= 160
                         else dirname for dirname in path.split('/')])

    def decrypt_server_message(self, line):
        """
        Decrypt encrypted strings within a server response.
        :param line: (str) server response
        :return: (str) the same message but with encrypted strings decrypted
        """
        return ' '.join([self._decrypt_path(word) if len(word) >= 160 else word for word in line.split(' ')])

    def login(self, user='', passwd='', acct=''):
        """
        Initialize a MyCipher object, encrypt the given username and derive the server password
        from the given password, then call the super-method with the results.
        Prints a security error message if such a message was received from the server.
        On no errors, call login_tag_verify (detailed below).
        """
        self._cipher = MyCipher(passwd)
        user = self._encrypt_filename(user)
        server_key = self._cipher.derive_server_key()
        resp = super().login(user, server_key, acct)
        try:
            resp = self.getresp()
        except error_perm as e:
            print('SECURITY ALERT -- ' + self.decrypt_server_message(str(e)[4:]), file=sys.stderr)
            return resp
        self.login_tag_verify()
        return resp

    def register(self, user, passwd, acct=''):
        """
        Register a new user. This works similarly to login but starts with an RGTR call instead of USER.
        The username is encrypted and the server password is derived from the given password.
        :param user: (str) username
        :param passwd: (str) secret
        :param acct: [unused]
        :return: (str) server response
        """
        self._cipher = MyCipher(passwd)
        user = self._encrypt_filename(user)
        resp = self.sendcmd('RGTR ' + user)
        if resp[0] == '3':
            server_key = self._cipher.derive_server_key()
            resp = self.sendcmd('PASS ' + server_key)
        if resp[0] == '3':
            resp = self.sendcmd('ACCT ' + acct)
        if resp[0] != '2':
            raise error_reply(resp)
        return resp

    def retrbinary(self, cmd, callback, blocksize=8192, rest=None):
        """
        Encrypt the filename, then receive all data from the super-method (file download) and decrypt it.
        Then call callback on the decrypted data in blocks (callback should write to local file).
        Prints a security error message if the file data verification failed.
        """
        retrcmd, path = cmd.split()
        enc_path = self._encrypt_path(path)
        try:
            with io.BytesIO() as buf:
                resp = super().retrbinary(' '.join((retrcmd, enc_path)), buf.write, blocksize, rest)
                buf.flush()
                dec_bytes = self._cipher.decrypt(buf.getvalue())
            with io.BytesIO(dec_bytes) as buf:
                while True:
                    b = buf.read(blocksize)
                    if not b:
                        break
                    callback(b)
            return resp
        except (error_perm, InvalidSignature) as e:
            if not (isinstance(e, InvalidSignature) or str(e).startswith('555')):
                raise e
            print('SECURITY ALERT -- The file %s has been altered! Download aborted' % path, file=sys.stderr)
            return None

    def storbinary(self, cmd, fp, blocksize=8192, callback=None, rest=None):
        """
        Encrypt the filename and file contents, then call the super-method with them (file upload).
        After the upload is done, send its MAC tag to the server and call exchange_meta_tag (detailed below).
        """
        storcmd, path = cmd.split()
        enc_path = self._encrypt_path(path)
        enc_bytes, tag = self._cipher.encrypt(fp.read())
        super().storbinary(' '.join((storcmd, enc_path)), io.BytesIO(enc_bytes), blocksize, callback, rest)

        # send tag
        resp = self.getresp()
        if resp[0] == '3':
            self.voidcmd('TAG ' + tag.hex())
        return self.exchange_meta_tag()

    def retrlines(self, cmd, callback=None):
        """
        Decrypt filenames received from LIST or NLST commands and return the result.
        """
        if cmd not in ('LIST', 'NLST'):
            return super().retrlines(cmd, callback)
        if callback is None:
            callback = print

        return super().retrlines(cmd, lambda line: callback(self._decrypt_path(line)))

    def exchange_meta_tag(self):
        """"
        Send a MAC tag for the server files' metadata by requesting the metadata
        and running the HMAC algorithm on it.
        This exchange follows every updating operation: storbinary, rename, delete, mkd, rmd
        :return: (Union(str, None)) server response or None on error
        """
        with io.BytesIO() as buf:
            try:
                return super().retrbinary('META', buf.write, 8192, None)
            except error_reply as e:
                if str(e)[0] != '3':
                    return None
                buf.flush()
                metatag = self._cipher.get_hmac_tag(buf.getvalue())
                return self.voidcmd('METATAG ' + metatag.hex())

    def login_tag_verify(self):
        """
        Authenticate the files on server by requesting the file metadata and its tag
        and calling the HMAC verification method on them.
        Prints a security error message if the authentication failed.
        """
        with io.BytesIO() as buf:
            super().retrbinary('LGMETA', buf.write, 8192, None)
            self.voidresp()
            buf.flush()
            metatag = bytes.fromhex(self.voidcmd('LGVF')[4:])
            try:
                if metatag:
                    self._cipher.authenticate_hmac(buf.getvalue(), metatag)
            except InvalidSignature:
                print('SECURITY ALERT -- Filesystem may be compromised', file=sys.stderr)

    def rename(self, fromname, toname):
        super().rename(self._encrypt_path(fromname), self._encrypt_path(toname))
        return self.exchange_meta_tag()

    def delete(self, filename):
        super().delete(self._encrypt_path(filename))
        return self.exchange_meta_tag()

    def cwd(self, dirname):
        return super().cwd(self._encrypt_path(dirname))

    def size(self, filename):
        self.sendcmd('TYPE I')
        return super().size(self._encrypt_path(filename))

    def mkd(self, dirname):
        super().mkd(self._encrypt_path(dirname))
        return self.exchange_meta_tag()

    def rmd(self, dirname):
        super().rmd(self._encrypt_path(dirname))
        return self.exchange_meta_tag()

    def nlst(self, *args):
        return ', '.join(super().nlst(*args))

    def upload_file(self, filename):
        """
        Call storbinary to upload a file.
        :param filename: (str) filename of the local file to upload
        :return: (str) server response
        """
        return self.storbinary('STOR ' + filename, open(filename, 'rb'))

    def download_file(self, filename):
        """
        Call retrbinary to download a file into a local file.
        If the download failed, delete the local file.
        :param filename: (str) filename (or path) of the requested file to download
        :return: (str) server response
        """
        try:
            with open(filename.split('/')[-1], 'wb') as outfile:
                resp = self.retrbinary('RETR ' + filename, outfile.write)
            if not resp:
                os.remove(filename.split('/')[-1])
            return resp
        except error_perm as e:
            os.remove(filename.split('/')[-1])
            raise e

    def client_op(self, *args):
        """
        Call an ftp method an print its response (decrypt if necessary).
        :param args: (str[]) the method name followed by its parameters
        :return: (MyFTPClient) this FTP object
        """
        method = getattr(MyFTPClient, args[0])
        args = [input('Please enter a %s\n' % arg) for arg in args[1:]]
        resp = method(self, *args)
        if resp:
            print(self.decrypt_server_message(resp) if isinstance(resp, str) else resp)
        return self

    def client_logout(self):
        resp = self.quit()
        print(self.decrypt_server_message(resp))
        return None

    @staticmethod
    def client_register(ftp):
        username = input('Please enter a username\n')
        password = input('Please enter a password\n')
        with MyFTPClient(ip) as ftp:
            resp = ftp.register(username, password)
            print(ftp.decrypt_server_message(resp))
        return None

    @staticmethod
    def client_login(ftp):
        username = input('Please enter a username\n')
        password = input('Please enter a password\n')
        ftp = MyFTPClient(ip)
        resp = ftp.login(username, password)
        if resp:
            print(ftp.decrypt_server_message(resp))
        return ftp

    @staticmethod
    def client_quit(ftp):
        sys.exit()


logged_out_menu = [
    {
        'name': 'Register',
        'fun': MyFTPClient.client_register,
        'args': []
    },
    {
        'name': 'Log in',
        'fun': MyFTPClient.client_login,
        'args': []
    },
    {
        'name': 'Quit',
        'fun': MyFTPClient.client_quit,
        'args': []
    }
]


logged_in_menu = [
    {
        'name': 'List files',
        'fun': MyFTPClient.client_op,
        'args': ['nlst']
    },
    {
        'name': 'Upload file',
        'fun': MyFTPClient.client_op,
        'args': ['upload_file', 'filename']
    },
    {
        'name': 'Download file',
        'fun': MyFTPClient.client_op,
        'args': ['download_file', 'filename']
    },
    {
        'name': 'Rename file or folder',
        'fun': MyFTPClient.client_op,
        'args': ['rename', 'filename', 'new name']
    },
    {
        'name': 'Get file size',
        'fun': MyFTPClient.client_op,
        'args': ['size', 'filename']
    },
    {
        'name': 'Delete file',
        'fun': MyFTPClient.client_op,
        'args': ['delete', 'filename']
    },
    {
        'name': 'Create folder',
        'fun': MyFTPClient.client_op,
        'args': ['mkd', 'dirname']
    },
    {
        'name': 'Delete folder',
        'fun': MyFTPClient.client_op,
        'args': ['rmd', 'dirname']
    },
    {
        'name': 'Change working directory',
        'fun': MyFTPClient.client_op,
        'args': ['cwd', 'dirname']
    },
    {
        'name': 'Show current working directory',
        'fun': MyFTPClient.client_op,
        'args': ['pwd']
    },
    {
        'name': 'Log out',
        'fun': MyFTPClient.client_logout,
        'args': []
    }
]


def display_menu(menu):
    print('Choose an operation:')
    for idx, menu_item in enumerate(menu):
        print('%d. %s' % (idx + 1, menu_item['name']))


def main():
    global ip

    if not os.path.exists('../client'):
        os.mkdir('../client')
    os.chdir('../client')

    ip = input('IP (leave blank for \'localhost\'): ').strip() or ip

    ftp = None
    while True:
        menu = logged_in_menu if ftp else logged_out_menu
        display_menu(menu)
        try:
            choice = int(input().strip())
            menu_item = menu[choice - 1]
            ftp = menu_item['fun'](ftp, *menu_item['args'])
        except (ValueError, IndexError):
            print('Invalid input', file=sys.stderr)
        except error_perm as e:
            print(e, file=sys.stderr)
        except (EOFError, OSError) as e:
            print('Server error: %s' % e, file=sys.stderr)
            ftp = None
        print()


if __name__ == '__main__':
    main()
