all: server client

server: server_main.o 
	gcc -o server server_main.o 

client: client_main.o getFileSize.o
	gcc -o client client_main.o getFileSize.o

client_main.o: client_main.c
	gcc -c client_main.c

server_main.o: server_main.c
	gcc -c server_main.c

getFileSize.o:getFileSize.c
	gcc -c getFileSize.c
