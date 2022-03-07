#include<iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include<stdlib.h>
#include<netinet/in.h>

#define PORT 8050
#define BUFFER_SIZE 50
class client
{
public:
  int client_socket;
  struct sockaddr_in client_address;

  client()
  {
    client_socket = socket(AF_INET, SOCK_DGRAM, 0);
    if (client_socket == 0)
    {
      printf( "Client Socket Failed\n");
      return;
    }
    printf( "Client Socket created\n");
    client_address.sin_family = AF_INET;
    client_address.sin_addr.s_addr = INADDR_ANY;
    client_address.sin_port = htons(PORT);
    if (connect(client_socket, (struct sockaddr *)&client_address, sizeof(client_address)) < 0)
    {
        printf( "Connection Failed from Client\n");
        return;
    }
    printf( "Client connection Success\n");
  }

  int send_to_server(char *msg)
  {
    sendto(client_socket, msg, BUFFER_SIZE, 0, (struct sockaddr*) NULL, sizeof(client_address) );
    printf( "Message Sent from Client:\n%s\n", msg);
    return 1;
  }
  int receive_from_server()
  {
    char buffer[BUFFER_SIZE];
    recvfrom(client_socket, buffer, BUFFER_SIZE, 0, (struct sockaddr*)NULL, NULL);
    printf("Message Recieved from Server:\n%s\n", buffer);
    return 1;
  }
};

class server
{
public:
    int server_socket;
    struct sockaddr_in server_address;
    server()
    {
      server_socket = socket(AF_INET, SOCK_DGRAM, 0);
      if (server_socket == 0)
      {
        printf( "Server Socket Failed\n");
        return;
      }
      printf( "Server Socket created\n");
      server_address.sin_family = AF_INET;
      server_address.sin_addr.s_addr = INADDR_ANY;
      server_address.sin_port = htons(PORT);
      if (bind(server_socket, (struct sockaddr*)&server_address, sizeof(server_address)) < 0)
      {
        printf( "Connection Failed from Server\n");
        return;
      }
      printf( "Server bound to PORT\n");
    }
    int receive_from_client(struct sockaddr_in* client_address)
    {
      char buffer[BUFFER_SIZE];
      unsigned int len = sizeof(*client_address);
      recvfrom(server_socket, buffer, BUFFER_SIZE, 0, (struct sockaddr*)client_address, &len);
      printf("Message Recieved from Client:\n%s\n", buffer);
      return 1;
    }
    int send_to_client(char *msg, struct sockaddr_in* client_address)
    {
      int len = sizeof(*client_address);
      sendto(server_socket, msg, BUFFER_SIZE, 0, (struct sockaddr*)client_address, len);
      printf("Message Sent from Server:\n%s\n", msg);
      return 1;
    }
};

int main()
{
  server *s = new server();
  client *c = new client();
  char msgSent[] = "Hello I am Anant";
  // c->send_to_server(msgSent);
  // printf("\n");
  // s->receive_from_client(&(c->client_address));
  // s->send_to_client(msgSent, &(c->client_address));
  // c->receive_from_server();
  return 0;

}
