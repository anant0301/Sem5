#include "headers.h"
int init_router(Router * new)
{
    new-> serv_addr.sin_family = AF_INET;
    new-> serv_addr.sin_port = htons(PORT);
    new-> serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    new-> serv_sock = socket(AF_INET, SOCK_STREAM, 0);
    new-> length = sizeof(new-> serv_addr);
    if(bind(new-> serv_sock, (SA_in *) &(new-> serv_addr), new-> length) == -1)
    {
        printf("Binding Failure\n");
        return -1;
    }
    return new-> serv_sock;
}