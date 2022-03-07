/*
created by Anant Patel
COE18B004
*/
#include "headers.h"
#include "udpServer.h"

udpServer::udpServer(int sock_fd)
{
  this->server_socket = sock_fd;

  // this->server_socket = socket(AF_INET, SOCK_DGRAM, 0);
  // if (this->server_socket == 0)
  // {
  //   printf( "Server Socket Failed\n");
  //   return;
  // }
  // printf( "Server Socket created\n");
  this->server_address.sin_family = AF_INET;
  this->server_address.sin_addr.s_addr = INADDR_ANY;
  this->server_address.sin_port = htons(PORT);
  if (bind(this->server_socket, (struct sockaddr*)&this->server_address, sizeof(this->server_address)) < 0)
  {
    printf( "Connection Failed from Server\n");
    return;
  }
    printf( "Server bound to PORT\n");
}
int udpServer::receive_from_client(struct sockaddr_in* client_address, char *buffer)
{
  // char buffer[BUFFER_SIZE];
  unsigned int len = sizeof(*client_address);
  int n = recvfrom(this->server_socket, buffer, BUFFER_SIZE, MSG_WAITALL, (struct sockaddr*)client_address, &len);
  buffer[n] = '\0';
  printf("Message Recieved from Client:\n%s\n", buffer);
  return n;
}
int udpServer::send_to_client(char *msg, struct sockaddr_in* client_address)
{
  int len = sizeof(*client_address);
  sendto(this->server_socket, msg, BUFFER_SIZE, 0, (struct sockaddr*)client_address, len);
  printf("Message Sent from Server:\n%s\n", msg);
  return 1;
}
void udpServer::close_server()
{
  close(this->server_socket);
  printf("Server Socket closed\n");
}
