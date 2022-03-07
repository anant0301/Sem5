#include<stdio.h>
#include<sys/socket.h>
#include<stdlib.h>
#include<netinet/in.h>

int main()
{
  char msg[] = "Trying Scoket Programming in C";
  int sfd = socket(AF_INET, SOCK_DGRAM, 0);
  if (sfd == 0)
  {
    printf("Socket Failed\n" );
    exit(EXIT_FAILURE);
  }
  struct sockaddr_in address;
  address.sin_family = AF_INET;
  address.sin_addr.s_addr = INADDR_ANY;
  address.sin_port = htons(8080);
  if(bind(sfd, (struct sockaddr*) &address, sizeof(address)) < 0);
  {
    printf("Sending Failure\n" );
    exit(EXIT_FAILURE);

  }
  close(sfd);
  printf("Socket Closed\n");
  return 0;

}
