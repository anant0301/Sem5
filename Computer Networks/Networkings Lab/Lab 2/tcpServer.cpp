/*
created by Anant Patel
COE18B004
*/
#include "headers.h"
#include "tcpServer.h"

tcpServer::tcpServer(int sock_fd)
{
  this->server_address.sin_family = AF_INET;
  this->server_address.sin_addr.s_addr = htonl(INADDR_ANY);
  this->server_address.sin_port = htons(PORT);
  if (bind(sock_fd, (struct sockaddr*)&this->server_address, sizeof(this->server_address)) < 0)
  {
    printf( "Connection Failed from Server\n");
    return;
  }
    printf( "Server bound to PORT\n");
}
int tcpServer::serverListen(int sock_fd, int backlog)
{
  if(listen(sock_fd, backlog) != 0)
  {
    printf("Server listening Failed\n");
    return -1;
  }
  printf("Server listening\n");
  return 1;
}
int tcpServer::serverAccept(int sock_fd, struct sockaddr_in client_address)
{
  unsigned int len = sizeof(client_address);
  int n;
  if((n = accept(sock_fd, (struct sockaddr*)&client_address, &len)) < 0)
  {
    printf("Server accept failed\n");
    return -1;
  }
  printf("Server accept client\n");
  return n;
}
void tcpServer::serverRead(int sock_fd, char buffer[])
{
  read(sock_fd, buffer, BUFFER_SIZE);
  printf("Message received by server:\n%s\n", buffer);
}
void tcpServer::serverWrite(int sock_fd, char msg[])
{
  write(sock_fd, msg, BUFFER_SIZE);
  printf("Message sent by server:\n%s\n", msg);
}
void tcpServer::close_server(int sock_fd)
{
  close(sock_fd);
  printf("Socket closed\n");
}
