/*
created by Anant Patel
COE18B004
*/
#include "headers.h"
#include "udpClient.h"

using namespace std;

int main(int argc, char *argv[])
{
  int sock_fd = socket(AF_INET, SOCK_DGRAM, 0);
  if (sock_fd == 0)
  {
    printf( "Server Socket creation Failed\n");
    return 0;
  }
  udpClient *c = new udpClient(sock_fd);
  printf("Client all set\n");
  c->send_to_server(argv[1]);
  c->send_to_server(argv[2]);
  c->send_to_server(argv[3]);
  char answer[BUFFER_SIZE];
  c->receive_from_server(answer);
  printf("Answer:\n%s\n", answer);
  c->close_client();
  return 1;
}
