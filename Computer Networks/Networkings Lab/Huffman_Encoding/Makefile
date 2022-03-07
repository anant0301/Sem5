huffman_object = huffman_encoding_tree.o create_node.o in_tree.o from_tree.o \
 make_heap.o heapify.o delete_heap.o insert_heap.o create_tree.o traversal.o \
 constant_length_encoding.o

heap = make_heap.o heapify.o delete_heap.o insert_heap.o


send = send_tree.o getFileSize.o encode_send.o encoding_traversal.o
recv = recv_tree.o extract.o recv_decode.o

all: server client

server: server_main.o $(huffman_object) $(send)
	gcc -o server server_main.o $(huffman_object) $(send)

server_main.o: server_main.c
	gcc -c server_main.c

client: client_main.o $(recv) $(huffman_object)
	gcc -o client client_main.o $(recv) $(huffman_object)

client_main.o: client_main.c
	gcc -c client_main.c

huffman_encoding_tree.o: ./huffman_encoding/huffman_encoding_tree.c 
	gcc -c ./huffman_encoding/huffman_encoding_tree.c 

create_node.o: ./huffman_encoding/create_node.c
	gcc -c ./huffman_encoding/create_node.c
	
in_tree.o: ./huffman_encoding/in_tree.c 
	gcc -c ./huffman_encoding/in_tree.c 

from_tree.o: ./huffman_encoding/from_tree.c 
	gcc -c ./huffman_encoding/from_tree.c 

make_heap.o: ./huffman_encoding/make_heap.c 
	gcc -c ./huffman_encoding/make_heap.c 

heapify.o: ./huffman_encoding/heapify.c 
	gcc -c ./huffman_encoding/heapify.c 

delete_heap.o: ./huffman_encoding/delete_heap.c 
	gcc -c ./huffman_encoding/delete_heap.c 

insert_heap.o: ./huffman_encoding/insert_heap.c 
	gcc -c ./huffman_encoding/insert_heap.c 

create_tree.o: ./huffman_encoding/create_tree.c 
	gcc -c ./huffman_encoding/create_tree.c 

traversal.o: ./huffman_encoding/traversal.c
	gcc -c ./huffman_encoding/traversal.c

send_tree.o: send_tree.c 
	gcc -c send_tree.c

recv_tree.o: recv_tree.c
	gcc -c recv_tree.c

extract.o: extract.c 
	gcc -c extract.c 

getFileSize.o: getFileSize.c 
	gcc -c getFileSize.c 

encode_send.o: encode_send.c 
	gcc -c encode_send.c 

encoding_traversal.o: encoding_traversal.c 
	gcc -c encoding_traversal.c 

recv_decode.o: recv_decode.c 
	gcc -c recv_decode.c 

constant_length_encoding.o: ./huffman_encoding/constant_length_encoding.c 
	gcc -c ./huffman_encoding/constant_length_encoding.c 

clean: 
	rm -f ./*.o