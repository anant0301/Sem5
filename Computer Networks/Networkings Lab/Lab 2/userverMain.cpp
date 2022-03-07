/*
created by Anant Patel
COE18B004
*/
#include "headers.h"
#include "udpServer.h"
#include "arithematic.h"

using namespace std;

int main()
{
  int sock_fd = socket(AF_INET, SOCK_DGRAM, 0);
  if (sock_fd == 0)
  {
    printf( "Server Socket creation Failed\n");
    return 0;
  }
  struct sockaddr_in client_address;
  udpServer *s = new udpServer(sock_fd);
  printf("Server all set\n");
  char buffer[BUFFER_SIZE];

  s->receive_from_client(&client_address, buffer);
  int n1 = atoi(buffer);
  s->receive_from_client(&client_address, buffer);
  char option = buffer[0];
  s->receive_from_client(&client_address, buffer);
  int n2 = atoi(buffer);
  printf("%d %c %d\n", n1, option, n2 );

  char answer[BUFFER_SIZE];
  switch (option)
  {
    case '+':
    sprintf(answer, "%d", sum(n1, n2));
    // printf("Answer: %d\n", sum(n1, n2));
    break;
    case '-':
    sprintf(answer, "%d", diff(n1, n2));
    // printf("Answer: %d\n", diff(n1, n2));
    break;
    case '*':
    sprintf(answer, "%d", pro(n1, n2));
    // printf("Answer: %d\n", pro(n1, n2));
    break;
    case '/':
    sprintf(answer, "%f", quo(n1, n2));
    // printf("Answer: %-.f\n", quo(n1, n2));
    break;
    default:
    printf("Exit and socket closed\n");
    close(sock_fd);
    return 0;
  }
  printf("%s\n", answer);
  s->send_to_client(answer, &client_address);
  s->close_server();
  return 1;
}
