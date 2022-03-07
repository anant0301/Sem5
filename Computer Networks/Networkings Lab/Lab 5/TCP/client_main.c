#include"headers.h"

int main(int agrc, char *argv[])
{
	int sock = socket(AF_INET, SOCK_STREAM, 0);
	struct sockaddr_in client;
	char *filename = argv[1];
	char buf[bsize];
	int s_sock;
	
	if (sock == -1)
	{
		/*exit if failed socket creation*/
		perror("Client socket creation failed");
		exit(0);
	}
	bzero(&client, sizeof(client));
	/*
	make sure there isn't some value in the client variable
	this is not necessary per say but if we are to up scale this
	then the same can be used to connect to different servers and
	hence we have to reset it as new 
	*/
	FILE *fp = fopen(filename, "rb");
	if (fp == NULL)
	{
	/*	exit if the read file doesn't exists	*/
		perror("File path invalid or file doesn't exists\n");
		exit(0);	
	}
	/*  client specifications  */
	client.sin_family = AF_INET;
	client.sin_port = htons(PORT);
	if(inet_pton(AF_INET, "127.0.0.1", &client.sin_addr) == 0)
	{
	/*	exit if the the client can't connect to localhost	*/
		printf("Client Creation Problem\n");
		exit(1);
	}
	if((s_sock = connect(sock, (struct sockaddr*)&client, sizeof(client)))!= 0)
	{
	/*	exit if the connection to server socket fails	*/
		perror("connect()");
		exit(0);
	}
	printf("Connected to server\n");
	/*	get File size for the input file name  */
	sprintf(buf, "%ld", clock());
	write(sock, buf, bsize);
	bzero(buf, bsize);
	unsigned long int fsize = getFileSize(filename);
	/*send file size as string*/
	sprintf(buf, "%ld", fsize);
	write(sock, buf, bsize);
	char ch;
	clock_t t_taken;
	/*clock value taken*/
	t_taken = clock();
	printf("File Transfer begin\n");
	while(fsize-- && fsize > 0)
	{
		/*	read char from file and pass to server*/
		/*if strings are read than the character '\0' 
		is treated as string end instead of data*/
		ch = fgetc(fp);
		write(sock, &ch, 1);
	}
	/*	close file and socket*/
	printf("File Transfer end\n");

	fclose(fp);
	close(sock);
	return 0;
}
