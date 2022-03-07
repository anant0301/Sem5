#include "./headers/headers.h"

int client_main()
{
	int sock = socket(AF_INET, SOCK_STREAM, 0);
	struct sockaddr_in server_addr;
	socklen_t saddrlen = sizeof(struct sockaddr_in);
	char buf[BUFFER_SIZE];	
	if (sock == -1)
	{
		/*exit if failed socket creation*/
		perror("Server socket creation failur \n");
		exit(0);
	}
	/* server configuration to sockaddr_in */
	bzero(&server_addr, saddrlen);
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(PORT);
	if(inet_pton(AF_INET, "127.0.0.1", &server_addr.sin_addr) == 0)
	{
		/*exit if sockaserver_addr_in.sin_server_addr can't be connected to localhost */
		perror("Server port ssingment problem \n");
		exit(0);
	}
	printf("Initiating TCP...\n");
		if (connect(sock, (struct sockaddr*)&server_addr, sizeof(server_addr)) != 0) 
	{ 
        perror("connection with the server failed...\n"); 
        exit(0); 
	} 
	else
    {	
    	printf("connected to the server..\n");
    };

    // read(sock, buf, BUFFER_SIZE);
    // printf("%s\n", buf);
    // ques_ans(sock);
 //	read till the message appears 
 //    while(strcmp(buf, "Client choose options for the above question\n"))
	// {
		bzero(buf, BUFFER_SIZE);
		// recvfrom(sock, buf, BUFFER_SIZE, MSG_WAITALL, (struct sockaddr*)NULL, 0);
		read(sock, buf, BUFFER_SIZE);
		printf("%s\n", buf);
		bzero(buf, BUFFER_SIZE);
		// recvfrom(sock, buf, BUFFER_SIZE, MSG_WAITALL, (struct sockaddr*)NULL, 0);
		read(sock, buf, BUFFER_SIZE);
		printf("%s\n", buf);
		bzero(buf, BUFFER_SIZE);
		// recvfrom(sock, buf, BUFFER_SIZE, MSG_WAITALL, (struct sockaddr*)NULL, 0);
		read(sock, buf, BUFFER_SIZE);
		printf("%s\n", buf);
		bzero(buf, BUFFER_SIZE);
		// recvfrom(sock, buf, BUFFER_SIZE, MSG_WAITALL, (struct sockaddr*)NULL, 0);
		read(sock, buf, BUFFER_SIZE);
		printf("%s\n", buf);
		bzero(buf, BUFFER_SIZE);
		// recvfrom(sock, buf, BUFFER_SIZE, MSG_WAITALL, (struct sockaddr*)NULL, 0);
		read(sock, buf, BUFFER_SIZE);
		printf("%s\n", buf);
		bzero(buf, BUFFER_SIZE);
		// recvfrom(sock, buf, BUFFER_SIZE, MSG_WAITALL, (struct sockaddr*)NULL, 0);
		read(sock, buf, BUFFER_SIZE);
		printf("%s\n", buf);
	// }
	char ch[2];
	do{	
		printf("Type option for the question above a, b, c, d \n");
		scanf("%s", ch);
	}while(ch[0] != 'a' && ch[0] !='b' && ch[0] !='c' && ch[0] !='d');
	write(sock, &ch, 2);

    close(sock);
    printf("Client Closed\n");
    return 0;
}

int main(int argc, char const *argv[])
{
	client_main();

	/* code */
	return 0;
}