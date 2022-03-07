
all: client 
client: client_main.o client.o TCPclientSend.o getFileSize.o 
	gcc -o client client_main.o client.o TCPclientSend.o getFileSize.o
	
client_main.o:client_main.c headers.h
	gcc -c client_main.c
client.o:client.c headers.h
	gcc -c client.c
TCPclientSend.o:TCPclientSend.c headers.h
	gcc -c TCPclientSend.c
getFileSize.o: getFileSize.c headers.h
	gcc -c getFileSize.c
