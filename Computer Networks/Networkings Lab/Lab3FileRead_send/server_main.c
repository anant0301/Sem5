#include"headers.h"

int main(int argc, char*argv[])
{
	FILE *fp = fopen("server_write.mp4", "w");
	struct sockaddr_in server, other;
	char buffer[Buffersize];
	int c_sock;
	int saddrlen = sizeof(other);
	int backlog = 5;
	int sock = socket(AF_INET, SOCK_STREAM, 0);
	server.sin_family = AF_INET;
	server.sin_port = htons(PORT);
	server.sin_addr.s_addr = inet_addr("127.0.0.1");
	bind(sock, (struct sockaddr*)&server, saddrlen);
	listen(sock, 5);
	printf("Server accepted client connection\n");
	c_sock = accept(sock, (struct sockaddr*)&other, &saddrlen);
	printf("File written into server_write\n");
	while(read(c_sock, buffer, Buffersize) != 0){
		fputs(buffer, fp);
	}
	fclose(fp);
	close(sock);
	return 0;
}
