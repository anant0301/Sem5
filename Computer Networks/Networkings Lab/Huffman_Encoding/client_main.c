#include"headers.h"

int main(int agrc, char *argv[])
{
	int sock = socket(AF_INET, SOCK_STREAM, 0);
	struct sockaddr_in client;

	if (sock == -1)
	{
		/*exit if failed socket creation*/
		perror("Client socket creation failed");
		exit(0);
	}
	memset(&client, 0, sizeof(client));
	/*  client specifications  */
	client.sin_family = AF_INET;
	client.sin_port = htons(PORT);
	if(inet_pton(AF_INET, "127.0.0.1", &client.sin_addr) == 0)
	{
	/*	exit if the the client can't connect to localhost	*/
		printf("Client Creation Problem\n");
		exit(1);
	}
	if((connect(sock, (struct sockaddr*)&client, sizeof(client)))!= 0)
	{
	/*	exit if the connection to server socket fails	*/
		perror("connect()");
		exit(0);
	}
	printf("Connected to server\n");
	/*	get File size for the input file name  */
	
    // char  treeFile[] = "const_recv_tree.txt";
    char  treeFile[] = "var_recv_tree.txt";
	struct huffman_heap tree;
	tree.length = 0;
	recv_tree(sock, &tree, treeFile);
	printf("Tree size %d\n", tree.length);
	recv_decode(sock, &tree, argv[1]);
	printf("File transfer Completed\n");
	close(sock);
	printf("Client Socket Closed\n");
	return 0;
}
