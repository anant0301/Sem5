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

#define BACK_LOG 10         // while the server listening
#define PORT_LEN 10         // PORT length stored in the router 
#define MAX_DEVICES 4       // max devices that can be connected
#define IP_ADDR_LEN 16      // length of the string containing IP_ADDR

int serv_sock;              // socket having server sock descriptor
int client_sock;                 // the client socket descriptor

typedef struct router_device
{
    char device;
    char ip_addr[IP_ADDR_LEN];
    char port[PORT_LEN];
    int device_connected;
} router;                   // the router device  

typedef struct routing_table
{
    router devices[MAX_DEVICES];
} routing_table;            // the routing table of all the devices

routing_table rt;
#endif