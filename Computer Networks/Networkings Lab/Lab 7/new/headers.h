#ifndef headers
#define headers

#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#include<unistd.h>
#include<pthread.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>

#define SOCKERROR (-1)
#define BACK_LOG 10         // while the server listening
#define PORT_LEN 10         // PORT length stored in the router 
#define MAX_DEVICES 4       // max devices that can be connected
#define IP_ADDR_LEN 16      // length of the string containing IP_ADDR
#define MAX_STR_LEN 100     // the max length accepted in a string
#define PORT 9000
#define LIMIT 3
#define SA_in struct sockaddr_in
#define SA struct sockaddr

typedef struct routingTableElement
{
    int id;
    int distance;
    int router_sock;
} Element;


typedef struct router
{
    int port;
    int dev_id;
    int serv_sock;
    SA_in serv_addr;
    socklen_t length;
    char ip[IP_ADDR_LEN];
    Element conn_router[MAX_DEVICES - 1];
} Router;

int init();
int init_router(Router * new);

char ip_addr[MAX_DEVICES][IP_ADDR_LEN];
int conn_matrix[][MAX_DEVICES] = {
    {0, 1, 2, 0},
    {1, 0, 3, 1},
    {2, 3, 0, 0},
    {1, 2, 3, 4}
};
int device_id[MAX_DEVICES];
#endif