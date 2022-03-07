/*
created by Anant Patel
COE18B004
*/
#include "headers.h"
#include "udpClient.h"

udpClient::udpClient(int sock_fd)
{
  this->client_socket = sock_fd;
  // this->client_socket = socket(AF_INET, SOCK_DGRAM, 0);
  // if (this->client_socket == 0)
  // {
  //   printf( "Client Socket Failed\n");
  //   return;
  // }
  // printf( "Client Socket created\n");
  this->server_address.sin_family = AF_INET;
  this->server_address.sin_addr.s_addr = INADDR_ANY;
  this->server_address.sin_port = htons(PORT);
  if (connect(this->client_socket, (struct sockaddr *)&this->server_address, sizeof(this->server_address)) < 0)
  {
    printf( "Connection Failed from Client\n");
    return;
  }
  printf( "Client connection Success\n");
}
int udpClient::send_to_server(char *msg)
{
  sendto(this->client_socket, msg, BUFFER_SIZE, 0, (struct sockaddr*) NULL, sizeof(this->server_address) );
  printf( "Message Sent from Client:\n%s\n", msg);
  return 1;
}
int udpClient::receive_from_server(char *buffer)
{
  // char buffer[BUFFER_SIZE];
  int n = recvfrom(this->client_socket, buffer, sizeof(buffer), 0, (struct sockaddr*)NULL, NULL);
  buffer[n] = '\0';
  printf("Message Recieved from Server:\n%s\n", buffer);
  return n;
}
void udpClient::close_client()
{
  close(this->client_socket);
  printf("Client Socket closed\n");
}
