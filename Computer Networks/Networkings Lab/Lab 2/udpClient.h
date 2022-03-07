/*
created by Anant Patel
COE18B004
*/
class udpClient
{
public:
  int client_socket;
  struct sockaddr_in server_address;
  udpClient(int sock_fd);
  int send_to_server(char *msg);
  int receive_from_server(char *buffer);
  void close_client();
};
