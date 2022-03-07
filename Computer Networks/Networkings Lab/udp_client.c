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
  address.sin_port = htons(9009);
  if (connect(sfd, (struct sockaddr *)&address, sizeof(address)) < 0)
  {
      printf("Connection Failed \n");
      return -1;
  }
  sendto(sfd, msg, sizeof(msg), 0, (struct sockaddr*) &address, sizeof(address) );
  printf("Message Sent\n");
  close(sfd);
  printf("Socket Closed\n");
  return 0;

}
