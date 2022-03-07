/*
created by Anant Patel
COE18B004
*/
class tcpServer
{
public:
  struct sockaddr_in server_address;
  tcpServer(int sock_fd);
  int serverListen(int sock_fd, int backlog);
  int serverAccept(int sock_fd, struct sockaddr_in client_address);
  void serverRead(int sock_fd, char buffer[]);
  void serverWrite(int sock_fd, char msg[]);
  void close_server(int sock_fd);
};
