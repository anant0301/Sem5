/*
created by Anant Patel
COE18B004
*/
class tcpClient
{
public:
  struct sockaddr_in server_address;
  tcpClient(int sock_fd);
  void clientRead(int sock_fd, char buffer[]);
  void clientWrite(int sock_fd, char msg[]);
  void close_client(int sock_fd);
};
