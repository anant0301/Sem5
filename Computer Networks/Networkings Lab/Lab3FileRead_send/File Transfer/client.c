#include "headers.h"

int clientCreation(struct sockaddr_in* addr, char protocol[])
{
	int sock = socket(AF_INET, protocol[0] == 't' ? SOCK_STREAM:SOCK_DGRAM, 0);
	addr->sin_family = AF_INET;
	addr->sin_port = htons(PORT);
	if(inet_pton(AF_INET, "127.0.0.1", &addr->sin_addr) == 0)
	{
		printf("Client Creation Problem\n");
		exit(1);
	}
	connect(sock,(struct sockaddr*)&addr, sizeof(struct sockaddr));
	printf("The client is connected to server\n");
	return sock;
}
