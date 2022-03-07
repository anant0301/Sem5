#include"headers.h"

int main(int agrc, char *argv[])
{
	int sock = socket(AF_INET, SOCK_DGRAM, 0);
	struct sockaddr_in client;
	char *filename = argv[1];
	char buf[bsize];
	int s_sock;
	int slen = sizeof(client);
	FILE *fp = fopen(filename, "r");
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
	long int fsize = getFileSize(filename);
	/*send file size as string*/
	sprintf(buf, "%ld", fsize);
	sendto(sock, buf, bsize, 0, (struct sockaddr*)&client, slen);
	char ch;
	printf("File Transfer begin\n");
	clock_t t_taken;
	/*clock value taken*/
	t_taken = clock();
	while(fsize-- && fsize > 0)
	{
		/*	reset the buffer contents to \0	*/
		bzero(buf, bsize);
		/*  
		it is necessary to send characters as the by sending string
		the end of string is found by the compiler is in '\0' and in
		some files this is used as a geniune read character rather than the 
		end of file 
		*/
		ch = fgetc(fp);
		/*
		send the character to the server through socket
		*/
		sendto(sock, &ch, 2, MSG_CONFIRM, (struct sockaddr*)&client, slen);
	}
	t_taken = clock() - t_taken;
	/*get clock cycles taken in the above operation*/
	printf("File Transfer complete\n");	
	printf("Time taken for Transfer: %f seconds\n", ((double)t_taken/CLOCKS_PER_SEC));
	/*  pass the exit signal telling the server to stop the recv from socket */
	char exit[] = "exit"; 
	sendto(sock, exit, 4, MSG_CONFIRM, (struct sockaddr*)&client, slen);

	/*  close file and socket  */
	fclose(fp);
	close(sock);
	return 0;
}
