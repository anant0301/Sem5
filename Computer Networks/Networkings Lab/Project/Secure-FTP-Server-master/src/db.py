import sqlite3
import os
import json

users_db = os.path.realpath('../server/users.db')


class FileMetaHandler(object):
    """
    Handles file metadata storage per user (root) with SQLite.
    File metadata includes 2 tables: Filenums and FileMetadata.
    Filenums contains mappings between FTP file paths and physical paths (numbers, AKA numpaths). More details
    explained in the MyDBFS class in server.py.
    FileMetadata stores file sizes and MAC tags for uploaded files.
    """

    def __init__(self, homedir):
        self.homedir = str(homedir)
        self.root = os.path.realpath(self.homedir)
        self.meta_db_path = self.root + os.sep + 'file_metadata.db'

    def create_file_metadata(self):
        file_meta_existed = os.path.isfile(self.meta_db_path)
        with sqlite3.connect(self.meta_db_path) as dbcon:
            cursor = dbcon.cursor()
            if not file_meta_existed:
                cursor.execute("""CREATE TABLE Filenums (
                                            filenum INTEGER PRIMARY KEY NOT NULL,
                                            numpath TEXT NOT NULL,
                                            ftppath TEXT NOT NULL)""")
                cursor.execute("""CREATE TABLE FileMetadata (
                                tag TEXT NOT NULL,
                                size INTEGER NOT NULL,
                                filenum INTEGER NOT NULL,
                                FOREIGN KEY (filenum) REFERENCES Filenums(filenum))""")
                cursor.execute("""INSERT INTO Filenums VALUES (?, ?, ?)""", (int(self.homedir), self.root, '/'))
        open(self.root + os.sep + 'mtag', 'wb')

    def add_file_meta(self, _filenum, _tag, _size):
        with sqlite3.connect(self.meta_db_path) as dbcon:
            cursor = dbcon.cursor()
            cursor.execute("""INSERT INTO FileMetadata VALUES (?,?,?)""", (_tag, _size, _filenum))
            return cursor.lastrowid

    def update_file_meta(self, _filenum, _tag, _size):
        with sqlite3.connect(self.meta_db_path) as dbcon:
            cursor = dbcon.cursor()
            cursor.execute("""UPDATE FileMetadata SET tag = (?), size = (?)
                              WHERE filenum = (?)""", (_tag, _size, _filenum))

    def update_filenum_in_meta(self, _old_filenum, _new_filenum):
        with sqlite3.connect(self.meta_db_path) as dbcon:
            cursor = dbcon.cursor()
            cursor.execute("""UPDATE FileMetadata SET filenum = (?)
                              WHERE filenum = (?)""", (_new_filenum, _old_filenum))

    def fetch_tag(self, _filenum):
        with sqlite3.connect(self.meta_db_path) as dbcon:
            cursor = dbcon.cursor()
            cursor.execute("""SELECT tag FROM FileMetadata WHERE filenum = (?)""", (_filenum,))
            return cursor.fetchone()

    def fetch_size(self, _filenum):
        with sqlite3.connect(self.meta_db_path) as dbcon:
            cursor = dbcon.cursor()
            cursor.execute("""SELECT size FROM FileMetadata WHERE filenum = (?)""", (_filenum,))
            return cursor.fetchone()

    def fetch_all_file_sizes(self):
        with sqlite3.connect(self.meta_db_path) as dbcon:
            cursor = dbcon.cursor()
            cursor.execute("""SELECT numpath, ftppath, size FROM FileMetadata
                              INNER JOIN Filenums ON Filenums.filenum = FileMetadata.filenum""")
            return cursor.fetchall()

    def add_numpath(self, _filenum, _numpath, _ftppath):
        with sqlite3.connect(self.meta_db_path) as dbcon:
            cursor = dbcon.cursor()
            cursor.execute("""INSERT INTO Filenums VALUES (?,?,?)""", (_filenum, _numpath, _ftppath))
            return cursor.lastrowid

    def fetch_filenum(self, _ftppath):
        with sqlite3.connect(self.meta_db_path) as dbcon:
            cursor = dbcon.cursor()
            cursor.execute("""SELECT serial_num FROM Filenums WHERE ftppath = (?)""", (_ftppath,))
            return cursor.fetchone()

    def fetch_numpath_by_ftppath(self, _ftppath):
        with sqlite3.connect(self.meta_db_path) as dbcon:
            cursor = dbcon.cursor()
            cursor.execute("""SELECT numpath FROM Filenums WHERE ftppath = (?)""", (_ftppath,))
            return cursor.fetchone()

    def fetch_numpath_by_filenum(self, _filenum):
        with sqlite3.connect(self.meta_db_path) as dbcon:
            cursor = dbcon.cursor()
            cursor.execute("""SELECT numpath FROM Filenums WHERE filenum = (?)""", (_filenum,))
            return cursor.fetchone()

    def fetch_filepath(self, _numpath):
        with sqlite3.connect(self.meta_db_path) as dbcon:
            cursor = dbcon.cursor()
            cursor.execute("""SELECT ftppath FROM Filenums WHERE numpath = (?)""", (_numpath,))
            return cursor.fetchone()

    def fetch_filename(self, _filenum):
        with sqlite3.connect(self.meta_db_path) as dbcon:
            cursor = dbcon.cursor()
            cursor.execute("""SELECT ftppath FROM Filenums WHERE filenum = (?)""", (_filenum,))
            ftppath = cursor.fetchone()
            if ftppath:
                ftppath = ftppath[0].split('/')[-1]
            return ftppath

    def fetch_all_files(self):
        with sqlite3.connect(self.meta_db_path) as dbcon:
            cursor = dbcon.cursor()
            cursor.execute("""SELECT ftppath, numpath FROM Filenums""")
            return cursor.fetchall()

    def remove_filenum(self, _filenum):
        with sqlite3.connect(self.meta_db_path) as dbcon:
            cursor = dbcon.cursor()
            cursor.execute("""DELETE FROM Filenums WHERE filenum = (?)""", (_filenum,))
            return cursor.fetchone()

    def get_next_filenum(self):
        with sqlite3.connect(self.meta_db_path) as dbcon:
            cursor = dbcon.cursor()
            cursor.execute("""SELECT MAX(filenum) FROM Filenums""")
            max_num = cursor.fetchone()[0]
            return (max_num + 1) if max_num is not None else 0

    def remove_file_by_num(self, _filenum):
        with sqlite3.connect(self.meta_db_path) as dbcon:
            cursor = dbcon.cursor()
            cursor.execute("""DELETE FROM FileMetadata WHERE filenum = (?)""", (_filenum,))
            cursor.execute("""DELETE FROM Filenums WHERE filenum = (?)""", (_filenum,))
            return cursor.fetchone()

    def get_numpath(self, path):
        """
        Fetch a file's numpath from the DB, or creates one if doesn't exist.
        """
        numpath = self.fetch_numpath_by_ftppath(path)
        if not numpath:
            new_num = self.get_next_filenum()
            parent_ftppath = '/'.join(path.split('/')[:-1]) or '/'
            parent_numpath = self.fetch_numpath_by_ftppath(parent_ftppath)[0]
            numpath = os.sep.join((parent_numpath, str(new_num)))
            self.add_numpath(new_num, numpath, path)
        else:
            numpath = numpath[0]
        return numpath


def create_user_metadata():
    metadata_existed = os.path.isfile(users_db)
    with sqlite3.connect(users_db) as dbcon:
        cursor = dbcon.cursor()
        if not metadata_existed:
            cursor.execute("""CREATE TABLE Users (
                            username TEXT PRIMARY KEY NOT NULL,
                            homedir TEXT NOT NULL,
                            perm TEXT NOT NULL,
                            operms NOT NULL,
                            msg_login TEXT NOT NULL,
                            msg_quit TEXT NOT NULL,
                            salt TEXT NOT NULL,
                            hashed_pass BLOB NOT NULL)""")


def add_user_metadata(username, homedir, perm, operms, msg_login, msg_quit, salt, hashed_pass):
    with sqlite3.connect(users_db) as dbcon:
        cursor = dbcon.cursor()
        cursor.execute("""INSERT INTO Users VALUES (?, ?, ?, ?, ?, ?, ?, ?)""",
                       (username, homedir, perm, json.dumps(operms), msg_login, msg_quit, salt, hashed_pass))
        return cursor.lastrowid


def remove_user_metadata(username):
    with sqlite3.connect(users_db) as dbcon:
        cursor = dbcon.cursor()
        cursor.execute("""DELETE FROM Users WHERE username = (?)""", (username,))
        return cursor.lastrowid


def fetch_user_metadata(username):
    with sqlite3.connect(users_db) as dbcon:
        cursor = dbcon.cursor()
        cursor.execute("""SELECT homedir, perm, msg_login, msg_quit FROM Users WHERE username = (?)""", (username,))
        return cursor.fetchone()


def fetch_operms(username):
    with sqlite3.connect(users_db) as dbcon:
        cursor = dbcon.cursor()
        cursor.execute("""SELECT operms FROM Users WHERE username = (?)""", (username,))
        return json.loads(cursor.fetchone()[0])


# Returns a tuple containing the salt and hashed password of a given username
def fetch_user_pass(_name):
    with sqlite3.connect(users_db) as dbcon:
        cursor = dbcon.cursor()
        cursor.execute("""SELECT salt, hashed_pass FROM Users WHERE username = (?)""", (_name,))
        return cursor.fetchone()


def fetch_next_user_num():
    with sqlite3.connect(users_db) as dbcon:
        cursor = dbcon.cursor()
        cursor.execute("""SELECT Count(*) FROM Users""")
        return cursor.fetchone()[0]+1


def has_user(_name):
    if fetch_user_pass(_name):
        return 1
    return 0
