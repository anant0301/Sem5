/*
created by Anant Patel
COE18B004
*/
#include "headers.h"
#include "tcpClient.h"


int main(int argc, char *argv[])
{
  int sock_fd = socket(AF_INET, SOCK_STREAM, 0);
  if (sock_fd == 0)
  {
    printf( "Server Socket creation Failed\n");
    return 0;
  }
  printf("%s %s %s \n",argv[1], argv[2], argv[3] );
  tcpClient *c = new tcpClient(sock_fd);
  printf("Client all set\n");
  c->clientWrite(sock_fd, argv[1]);
  c->clientWrite(sock_fd, argv[2]);
  c->clientWrite(sock_fd, argv[3]);
  char answer[BUFFER_SIZE];
  c->clientRead(sock_fd, answer);
  printf("Answer:\n%s\n", answer);
  c->close_client(sock_fd);
  return 1;
}
