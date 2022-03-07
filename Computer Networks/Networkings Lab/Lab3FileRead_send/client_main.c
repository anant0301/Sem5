#include"headers.h"

int main(int agrc, char *argv[])
{
	char string[Buffersize]; ;
	int sock = socket(AF_INET, SOCK_STREAM, 0);
	int fp = fopen("file_client_read.mp4", "r");
	struct sockaddr_in client;
	client.sin_family = AF_INET;
	client.sin_port = htons(PORT);
	client.sin_addr.s_addr = inet_addr("127.0.0.1");
	connect(sock, (struct sockaddr*)&client, sizeof(client));
	printf("Client connected to server\n");
/*	while(fgets(string, Buffersize, fp))
	{
		write(sock, string, Buffersize);
	}*/
	sendfile(sock, fp, NULL, Buffersize);
	printf("File read \n");
	close(sock);
	return 0;
}
