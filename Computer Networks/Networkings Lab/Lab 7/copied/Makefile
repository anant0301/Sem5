all: main

obj = get_router_index.o init_routing_table.o

main: main.o server_create.o client_create.o $(obj) 
	gcc -o main main.o server_create.o client_create.o $(obj)

$(obj): headers.h 
 
main.o: main.c 
	gcc -c main.c

server_create.o: server_create.c 
	gcc -c server_create.c

client_create.o: client_create.c 
	gcc -c client_create.c


clean: 
	rm *.o main