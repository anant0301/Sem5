#include "./headers/headers.h"

extern int get_quesno();
extern char pass_ques(int sock, int qno);

int server_main()
{
	int sock = socket(AF_INET, SOCK_STREAM, 0);
	struct sockaddr_in server_addr;
	int other_socket;
	struct sockaddr_in other_addr;
	socklen_t saddrlen = sizeof(struct sockaddr_in);
	char buf[BUFFER_SIZE] = "Client choose options for the above question\n";
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
		/*exit if sockaaddr_in.sin_addr can't be connected to localhost */
		perror("Server port ssingment problem \n");
		exit(0);
	}

	if(bind(sock, (struct sockaddr*)&server_addr, saddrlen) == -1)
	{
		perror("Server binding failure \n");
		exit(0);
	}

	printf("Initiating TCP...\n");
	if (listen(sock, 10) == -1)
	{
	/*	listen to client requesting access, maximum remember 5 clients	*/
		perror("Server listen error \n");
		exit(0);
	}
	if((other_socket = accept(sock, (struct sockaddr*)&other_addr, &saddrlen) == - 1))
	{
		/*  Server not accept client socket connection  */
		perror("Client server connected \n");
		exit(0);
	}
	write(other_socket, buf, BUFFER_SIZE);
	printf("Messaage Sent: %s\n", buf);


// get the question number from file and update for next client
	int qno = get_quesno();
// pass question to client and get the
	char ans = pass_ques(other_socket, qno);
// to stop client from reading further
	printf("%s\n", buf);
	write(other_socket, buf, BUFFER_SIZE);
// get answers from client
// get the question checked
	reset_quesnoFile();
	close(sock);
	printf("Server Closed\n");

// reset the file  to 0
	return 0;
}

int main(int argc, char const *argv[])
{
	server_main();

	/* code */
	return 0;
}