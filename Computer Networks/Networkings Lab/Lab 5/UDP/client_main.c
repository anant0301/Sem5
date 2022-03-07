#include"headers.h"

int main(int agrc, char *argv[])
{
	int sock = socket(AF_INET, SOCK_DGRAM, 0);
	struct sockaddr_in client;
	char *filename = argv[1];
	char buf[bsize];
	int s_sock;
	int slen = sizeof(client);
	FILE *fp = fopen(filename, "rb");
	/*
	make sure there isn't some value in the client variable
	this is not necessary per say but if we are to up scale this
	then the same can be used to connect to different servers and
	hence we have to reset it as new 
	*/

	if(sock == -1)
	{
		/*	exit if socket creation failed	*/
		perror("Client Socket creation failed");
		exit(0);
	}

	bzero(&client, slen);
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
	long int fsize = getFileSize(filename);
	/*send file size as string*/
	sprintf(buf, "%ld", fsize);
	write(sock, buf, bsize);
	char ch;
	printf("File Transfer begin\n");
	while(fsize-- > 0)
	{
		ch = fgetc(fp);
		write(sock, &ch, bsize);
	}
	printf("File Transfer complete\n");	
	/*  pass the exit signal telling the server to stop the recv from socket */
	char exit[] = "exit"; 
	printf("message sent %s\n", exit);
	write(sock, exit, 5);

	/*  close file and socket  */
	fclose(fp);
	close(sock);
	return 0;
}
