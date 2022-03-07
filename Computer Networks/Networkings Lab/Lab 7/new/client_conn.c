#include "headers.h"
void * client_connect(void * param)
{
    int router_id = *(int *)param;
    int client_sock = socket(AF_INET, SOCK_STREAM, 0);
    SA_in * serv_addr = malloc(sizeof(SA_in)); 
    serv_addr-> sin_family = AF_INET;
    serv_addr-> sin_port = htons(PORT);
    serv_addr-> sin_addr.s_addr = htonl(INADDR_ANY);
    socklen_t length = sizeof(SA);
    if(connect(client_sock, (SA *)&serv_addr, length) != 0)
    {
        perror("Client connection failure\n");
        return NULL;
    }
    
}