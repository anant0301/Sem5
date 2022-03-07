huffman_encode = huff_tree_test.o huffman_encoding_tree.o create_node.o in_tree.o \
 create_tree.o from_tree.o traversal.o

heap = make_heap.o heapify.o delete_heap.o insert_heap.o

all: huff_tree 

huff_tree: $(huffman_encode) $(heap)
	gcc -o huff_tree  $(huffman_encode) $(heap) 

huff_tree_test.o: huff_tree_test.c 
	gcc -c huff_tree_test.c 

huffman_encoding_tree.o: huffman_encoding_tree.c 
	gcc -c huffman_encoding_tree.c 

create_node.o: create_node.c
	gcc -c create_node.c
	
in_tree.o: in_tree.c 
	gcc -c in_tree.c 

from_tree.o: from_tree.c 
	gcc -c from_tree.c 

make_heap.o: make_heap.c 
	gcc -c make_heap.c 

heapify.o: heapify.c 
	gcc -c heapify.c 

delete_heap.o: delete_heap.c 
	gcc -c delete_heap.c 

insert_heap.o: insert_heap.c 
	gcc -c insert_heap.c 

create_tree.o: create_tree.c 
	gcc -c create_tree.c 

traversal.o: traversal.c 
	gcc -c traversal.c

clean: 
	rm -f ./*.o