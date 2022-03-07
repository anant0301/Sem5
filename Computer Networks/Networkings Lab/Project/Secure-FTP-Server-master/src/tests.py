import unittest
from mycrypto import MyCipher


class TestMyCrypto(unittest.TestCase):
    def setUp(self):
        self.secret = 'dog'

    def test_mycipher_text(self):
        lorem_ipsum = """
            Lorem ipsum dolor sit amet, consectetur adipiscing elit,
            sed do eiusmod tempor incididunt ut labore et dolore magna aliqua.
            Ut enim ad minim veniam, quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea commodo consequat.
            Duis aute irure dolor in reprehenderit in voluptate velit esse cillum dolore eu fugiat nulla pariatur.
            Excepteur sint occaecat cupidatat non proident, sunt in culpa qui officia deserunt mollit anim id est laborum.
        """
        ct = MyCipher(self.secret).encrypt(lorem_ipsum.encode())
        pt = MyCipher(self.secret).decrypt(ct).decode()
        self.assertEqual(lorem_ipsum, pt)

    def test_mycipher_filename(self):
        filename = 'potato.txt'
        ct1 = MyCipher(self.secret).encrypt(filename.encode(), is_filename=True)
        ct2 = MyCipher(self.secret).encrypt(filename.encode(), is_filename=True)
        self.assertEqual(ct1, ct2)

        pt = MyCipher(self.secret).decrypt(ct1).decode()
        self.assertEqual(filename, pt)


if __name__ == '__main__':
    unittest.main()
