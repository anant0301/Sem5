# Topics in Computer Security Mini-Project #

## Installation ##
### Setup (dependencies) ###
1. Install Python 3
1. Install the pyftpdlib library: run `pip install pyftpdlib`
1. Install the cryptography library: run `pip install cryptography`

### Running the program ###
1. Navigate to the src/ folder
1. Run the server:
   1. Open a command line window
   1. Run the command: `python server.py`
   1. Enter an IP or press enter for default (localhost)
1. Run the client:
   1. Open another command line window
   1. Run the command: `python client.py`
   1. Enter an IP or press enter for default (localhost)

## Usage ##
1. In the client, enter an action number (for example, `1` to register).
1. Enter the required info for the chosen action (filename etc.)
1. Enjoy!

## Features ##
### Basics ###
* Fully encrypted FTP client and server. Cryptography is done on the client side.
* Encrypted file system on the server side. All files are stored as serial numbers which are mapped to encrypted names.
* Notifies the user on unauthorized file changes.

### Extras ###
* Full support for directories (create, remove, rename, change working directory).
* Support for arbitrarily long file names.
