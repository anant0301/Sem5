/*
created by Anant Patel
COE18B004
*/
class udpServer
{
public:
  int server_socket;
  struct sockaddr_in server_address;
  udpServer(int sock_fd);
  int receive_from_client(struct sockaddr_in* client_address, char *buffer);
  int send_to_client(char *msg, struct sockaddr_in* client_address);
  void close_server();
};
