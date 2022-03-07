#include"headers.h"

int main(int argc, char *argv[])
{
	struct sockaddr_in server, other;
	int c_sock;
	char *filename = argv[1];
	int saddrlen = sizeof(other);
	int backlog = 5;
	int sock = socket(AF_INET, SOCK_STREAM, 0);
	bzero(&server, saddrlen);
	bzero(&other, saddrlen);	
	char buf[bsize];	
	FILE *fp;
	if (sock == -1)
	{
		/*exit if failed socket creation*/
		perror("Server socket creation failed");
		exit(0);
	}

	bzero(&server, saddrlen);
	/*
	make sure there isn't some value in the client variable
	this is not necessary per say but if we are to up scale this
	then the same can be used to connect to different servers and
	hence we have to reset it as new 
	*/
	bzero(&other, saddrlen);
	/*	server specifications*/
	server.sin_family = AF_INET;
	server.sin_port = htons(PORT);
	if(inet_pton(AF_INET, "127.0.0.1", &server.sin_addr) == 0)
	{
		/*exit if sockaaddr_in.sin_addr can't be connected to localhost */
		printf("Client Creation Problem\n");
		exit(1);
	}
	if (bind(sock, (struct sockaddr*)&server, saddrlen) != 0)
	{	
		/*	exit if the server socket can't be bound to port and host in sockadddr_in	*/
		perror("Server not bound: [error]" );
		exit(0);
	}
	else
	{
		/*	listen to client requesting access, maximum remember 5 clients	*/
		listen(sock, 5);
	}
	/*	accept client request for connection
	get client socket descriptor c_sock
	*/
	c_sock = accept(sock, (struct sockaddr*)&other, &saddrlen);
	printf("Server accepted client connection\n");
	fp = fopen(filename, "wb");

	clock_t time;
	read(c_sock, buf, bsize);
	time = atoi(buf);
	printf("Latency: %f \n", ((double)clock() - time)/CLOCKS_PER_SEC);
	bzero(buf, bsize);

	/*	get file size from the client*/
	read(c_sock, buf, bsize);
	printf("The file size is: %s\n", buf);
	/*	get numerical value of received client size*/
	unsigned long int fsize = atoi(buf);
	char ch;
	clock_t t_taken;
	/*clock value taken*/
	t_taken = clock();
	printf("File write Begin\n");
	while(fsize-- > 0) 
	{
		/*read from the client socket and write to file */
		read(c_sock, &ch, 1);
		fputc(ch, fp);
	}
	/*get clock cycles taken in the above operation*/
	t_taken = clock() - t_taken;
	printf("File Write Complete\nTime taken to write file: %f seconds\n", ((double)t_taken)/CLOCKS_PER_SEC);
	/*	close file and socket*/
	fclose(fp);
	close(sock);
	return 0;
}
