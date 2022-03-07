#include"headers.h"

int main(int argc, char *argv[])
{
	struct sockaddr_in server, other;
	int c_sock;
	int saddrlen = sizeof(other);
	int backlog = 5;
	int sock = socket(AF_INET, SOCK_STREAM, 0);
	memset(&server, 0, saddrlen);
	memset(&other, 0, saddrlen);	
	if (sock == -1)
	{
		/*exit if failed socket creation*/
		perror("Server socket creation failed");
		exit(0);
	}

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

	struct huffman_heap tree;
	char treeFile[] = "encoded_file.txt";
    FILE *write_fp = fopen(treeFile, "w");
	
	tree.length = 0;
    huffman_encoding_tree(argv[1], &tree);
    make_heap(&tree);
    fprintf(write_fp, "%d\n", tree.length);

    create_tree(&tree);
    tree.arr[0]-> code[0] = '\0'; 
    traversal(tree.arr[0], tree.arr[0]-> code, write_fp);
    fclose(write_fp);
	printf("Variable Length Encoding\n");
	struct huffman_heap newTree;
	newTree.length = 0;
	send_tree(c_sock, &tree, treeFile);
	newTree.arr = calloc(sizeof(struct huffman_node*), MAX_TREE_SIZE);
	encoding_traversal(tree.arr[0], tree.arr[0]-> code, &newTree);
	encode_send(c_sock, &newTree, argv[1]);
	
	// printf("Constant Length Encoding\n");
	// constant_length_encoding(&tree, treeFile);
	// encode_send(c_sock, &tree, argv[1]);
	
	printf("File transfer Completed\n");
	close(sock);
	printf("Server Sock closes\n");
	return 0;
}
