#include"headers.h"

int main(int argc, char *argv[])
{

	struct sockaddr_in server, other;
	int c_sock;
	char *filename = argv[1];
	int saddrlen = sizeof(other);
	int backlog = 5;
	int sock = socket(AF_INET, SOCK_DGRAM, 0);
	bzero(&server, saddrlen);
	bzero(&other, saddrlen);	
	char buf[bsize];

	FILE *fp = fopen(filename, "w");
	if(sock == -1)
	{
		/*	exit if socket creation failed	*/
		perror("Server Socket creation failed");
		exit(0);
	}

	/*
	make sure there isn't some value in the client variable
	this is not necessary per say but if we are to up scale this
	then the same can be used to connect to different servers and
	hence we have to reset it as new 
	*/
	bzero(&server, saddrlen);
	/*  server specifications  */
	server.sin_family = AF_INET;
	server.sin_port = htons(PORT);
	if(inet_pton(AF_INET, "127.0.0.1", &server.sin_addr) == 0)
	{
	/*	exit if the the server can't connect to localhost	*/
		printf("Client Creation Problem\n");
		exit(1);
	}
	if (bind(sock, (struct sockaddr*)&server, saddrlen) != 0)
	{	
	/*	exit if server binding to socket created fails 	*/
		perror("Server not bound: [error]" );
		exit(0);
	}
	/*	Receive file size	*/
	int  n  = read(sock, buf, bsize);
	buf[n] = '\0';
	clock_t time;
	time = atoi(buf);
	printf("Latency : %lf\n", ((double)clock() - time)/CLOCKS_PER_SEC);

	bzero(buf, bsize);
	read(sock, buf, bsize);	
	printf("The file size is: %s\n", buf);
	/*	convert file size to numeric data type	*/
	long int fsize = atoi(buf);
	char ch[4];
	clock_t t_taken;
	/*clock value taken*/
	t_taken = clock();
	printf("File write Begin\n");
	while(fsize-- > 0 && strcmp(ch, "exit")) 
	{
		read(sock, ch, 4);
		fputc(ch[0], fp);
	}
	t_taken = clock() - t_taken;
	printf("File Write Complete\nTime taken to write file: %f seconds\n", ((double)t_taken)/CLOCKS_PER_SEC);
	/*	close file and socket*/
	fclose(fp);

	close(sock);

	return 0;
}
