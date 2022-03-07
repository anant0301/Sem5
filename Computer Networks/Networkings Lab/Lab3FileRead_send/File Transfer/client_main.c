#include"headers.h"



void chk_input(int argc, char *argv[]);
int main(int argc, char *argv[])
{
	if(argc != 3)
	{
		printf("Error: ./<executable> <tcp | udp> <readfile_client>");
		exit(0);
	}
	chk_input(argc, argv);
	// printf("File input correct");
	int cSocket;
	struct sockaddr_in client;
	FILE *fp = open(argv[2], "r");
	if(fp == NULL)
	{
		printf("File open fail\n");
		exit(1);
	}
	printf("File Size: %lld\n" ,getFileSize(argv[1]));
	
	cSocket = clientCreation(&client, argv[1]);
	TCPclientSend(cSocket, fp, client);
	return 0;
}

void chk_input(int argc, char *argv[])
{
	if (strcmp(argv[1], "tcp") != 0 && strcmp(argv[1], "udp") != 0)
	{
		printf("Error: ./<executable> <tcp | udp> <readfile_client>");
		exit(0);
	}
}
