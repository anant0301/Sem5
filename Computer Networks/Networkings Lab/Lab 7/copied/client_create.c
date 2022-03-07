#include "headers.h"
int client_create(int PORT, char * ip_addr)
{
    client_sock = socket(AF_INET, SOCK_STREAM, 0);
	struct sockaddr_in client;
	memset(&client, 0, sizeof(client));
	client.sin_family = AF_INET;
	client.sin_port = htons(PORT);
	client.sin_addr.s_addr = inet_addr(ip_addr);
	//client.sin_addr.s_addr = INADDR_ANY;
	if(connect(client_sock, (struct sockaddr *)&client, sizeof(client)) == -1)
	{
		printf("Connection Issue...\n");
		return 1;
	}
	else return 0;
}