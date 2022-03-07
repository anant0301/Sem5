/*
created by Anant Patel
COE18B004
*/
#include "headers.h"
#include "tcpClient.h"

tcpClient::tcpClient(int sock_fd)
{
  this->server_address.sin_family = AF_INET;
  this->server_address.sin_addr.s_addr = htonl(INADDR_ANY);
  this->server_address.sin_port = htons(PORT);
  if (connect(sock_fd, (struct sockaddr *)&this->server_address, sizeof(this->server_address)) < 0)
  {
    printf( "Connection Failed from Client\n");
    exit(0);
  }
  printf( "Client connection Success\n");
}
void tcpClient::clientRead(int sock_fd, char buffer[])
{
  read(sock_fd, buffer, BUFFER_SIZE);
  printf("Message received by client:\n%s\n", buffer);
}
void tcpClient::clientWrite(int sock_fd, char msg[])
{
  write(sock_fd, msg, BUFFER_SIZE);
  printf("Message sent by client:\n%s\n", msg);
}
void tcpClient::close_client(int sock_fd)
{
  close(sock_fd);
  printf("Socket closed\n");
}
