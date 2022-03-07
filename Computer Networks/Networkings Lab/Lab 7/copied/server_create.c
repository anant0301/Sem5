#include "headers.h"
int server_create(int PORT)
{
    serv_sock = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in server, other;
    server.sin_family = AF_INET;
    server.sin_port = htons(PORT);
    server.sin_addr.s_addr = INADDR_ANY;
    if (bind(serv_sock, (struct sockaddr*)&server, sizeof(server)) == -1)
    {
        printf("Server Creation Error!\n");
        return 0;
    }
    else
    {
        printf("Server Created Successfully..\n");
        listen(serv_sock, BACK_LOG);
        printf("Server Listening...\n");
        return 1;
    }
}