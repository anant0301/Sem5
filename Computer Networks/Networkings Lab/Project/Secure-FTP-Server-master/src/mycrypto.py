import os
from cryptography.hazmat.backends import default_backend
from cryptography.hazmat.primitives.ciphers import Cipher, algorithms, modes
from cryptography.hazmat.primitives.padding import PKCS7
from cryptography.hazmat.primitives import hashes, hmac
from cryptography.hazmat.primitives.kdf.hkdf import HKDF
from cryptography.hazmat.primitives.kdf.scrypt import Scrypt


class MyCipher(object):
    """
    An object responsible for encryption and decryption, as well as authentication and key derivation,
    according to the master secret given by the user when initializing the object.
    All cryptography operations are provided by the cryptography.hazmat python library.
    The encryption algorithm being used is AES with CBC, and for authentication - HMAC.
    Additionally, this class is used by the server for password storage and authentication.
    """

    def __init__(self, secret):
        self._secret = secret.encode()
        self._cipher_key = self.derive_key(self._secret + b'1')
        self._mac_key = self.derive_key(self._secret + b'2')

    def derive_server_key(self):
        return self.derive_key(self._secret + b'3').hex()

    def get_hmac_tag(self, data):
        """
        Run the HMAC algorithm on the given data and return the authentication tag.
        :param data: (bytes) data to authenticate
        :return: (bytes) MAC tag
        """
        h = hmac.HMAC(self._mac_key, hashes.SHA256(), default_backend())
        h.update(data)
        return h.finalize()

    def authenticate_hmac(self, data, tag):
        """
        Verify the given data with the given tag using HMAC. An exception is raised if verification fails.
        :param data: (bytes) data to verify
        :param tag: (bytes) MAC tag
        """
        h = hmac.HMAC(self._mac_key, hashes.SHA256(), default_backend())
        h.update(data)
        h.verify(tag)

    def encrypt(self, pt, is_filename=False):
        """
        Encrypt and authenticate the given plaintext using AES and HMAC.
        if is_filename is True, the IV will be deterministically generated (derived from secret||pt),
        and the returned data will all be concatenated (not a tuple)
        :param pt: (bytes) plaintext
        :param is_filename: (bool) encrypting for filename
        :return: encrypted data: Union(Tuple, bytes) (iv||ct, tag) or iv||ct||tag in case of filename
                    iv = initialization vector (128 bits)
                    ct = ciphertext (encrypted message)
                    tag = MAC tag (256 bits)
        """
        # pad the plaintext to make its size a multiple of 256 bits (for CBC)
        padder = PKCS7(256).padder()
        padded_pt = padder.update(pt) + padder.finalize()

        iv = self.derive_key(self._secret + pt)[:16] if is_filename else os.urandom(16)
        cipher = Cipher(algorithms.AES(self._cipher_key), modes.CBC(iv), default_backend())
        encryptor = cipher.encryptor()
        ct = encryptor.update(padded_pt) + encryptor.finalize()

        tag = self.get_hmac_tag(iv + ct)
        return iv + ct + tag if is_filename else (iv + ct, tag)

    def decrypt(self, msg):
        """
        Verify and decrypt the given message using AES and HMAC.
        :param msg: encrypted data (structure above)
        :return: (bytes) decrypted message plaintext (if verified)
        """
        if isinstance(msg, tuple):
            iv_and_ct, tag = msg
        else:
            iv_and_ct = msg[:-32]
            tag = msg[-32:]
        iv = iv_and_ct[:16]
        ct = iv_and_ct[16:]

        self.authenticate_hmac(iv_and_ct, tag)

        cipher = Cipher(algorithms.AES(self._cipher_key), modes.CBC(iv), default_backend())
        decryptor = cipher.decryptor()
        padded_pt = decryptor.update(ct) + decryptor.finalize()

        # unpad the decrypted plaintext (it was padded for CBC before encryption)
        unpadder = PKCS7(256).unpadder()
        return unpadder.update(padded_pt) + unpadder.finalize()

    @staticmethod
    def derive_key(key_material):
        """
        Deterministically derive a kay using HKDF (key derivation function provided by cryptography.hazmat)
        :param key_material: (bytes) material to derive key from
        :return: (bytes) derived key
        """
        return HKDF(hashes.SHA256(), 32, None, None, default_backend()).derive(key_material)

    @staticmethod
    def derive_password_for_storage(password):
        """
        Derive a password for storage on the server side, using a randomly generated salt.
        Uses Scrypt (a key derivation function for password storage, provided by cryptography.hazmat).
        :param password: (str) a password in hashed form (hex)
        :return: (Tuple(bytes)) the random salt and the derived password
        """
        salt = os.urandom(16)
        key = Scrypt(
            salt=salt,
            length=32,
            n=2 ** 14,
            r=8,
            p=1,
            backend=default_backend()
        ).derive(bytes.fromhex(password))
        return salt, key

    @staticmethod
    def verify_stored_password(password, salt, key):
        """
        Verify a stored password on the server side, using Scrypt.
        An exception is raised if verification fails.
        :param password: (bytes) a password in hashed form (hex)
        :param salt: (bytes) the random salt stored alongside the key
        :param key: (bytes) the stored password to verify against
        """
        Scrypt(
            salt=salt,
            length=32,
            n=2 ** 14,
            r=8,
            p=1,
            backend=default_backend()
        ).verify(bytes.fromhex(password), key)
