### Usage
```
make
```

```
./transfer <tcp | udp> <send | recv> <ip> <port> [filename]
```

### Note
First start the server, then send any file from client to server. Also calculates bytes sent/recieved and throughput.

**IMP: Don't run server and client from the same directory**


### Example
```
./transfer tcp recv 127.0.0.1 8080
./transfer tcp send 127.0.0.1 8080 file.txt

./transfer udp recv 127.0.0.1 8080
./transfer udp send 127.0.0.1 8080 file.txt
```
