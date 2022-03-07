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

	if (argc == 1)
	{
		filename = "temp.txt" ;
	}
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
	while(1)
	{
	/*	Receive file size	*/
		int  n  = recvfrom(sock, buf, bsize, 0, (struct sockaddr*)&other, &saddrlen);
		buf[n] = '\0';
		printf("The file size is: %s\n", buf);
		/*	convert file size to numeric data type	*/
		long int fsize = atoi(buf);
		char ch[4];
		clock_t t_taken;
		/*clock value taken*/
		t_taken = clock();
		printf("File write Begin\n");
		while(fsize-- && fsize > 0) 
		{
			/*	receive 4 characters as the last has to be exit and 
			thus check if exit signal is there every time if it is 
			there then break out of the loop
			*/
			recvfrom(sock, ch, 4, 0, (struct sockaddr*)&other, &saddrlen);
			if (strcmp(ch, "exit"))
				fputc(ch[0], fp);
			else
				break;
		}
		/*get clock cycles taken in the above operation*/
		t_taken = clock() - t_taken;
		printf("File Write Complete\nTime taken to write file: %f seconds\n", ((double)t_taken)/CLOCKS_PER_SEC);
		/*	close file and socket*/
		fclose(fp);
	}
	close(sock);

	return 0;
}
