#ifndef headers
#define headers

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <string.h>

#define PORT 9000
#define MAX_TREE_SIZE 256
#define BUFFER_SIZE 100
#define MAX_ENCODE_LEN 100

struct huffman_node
{
    int freq;
    char data;
    char code[MAX_ENCODE_LEN];
    struct huffman_node *left_;
    struct huffman_node *right_;
};
struct huffman_heap
{
    struct huffman_node **arr;
    int length;
    // int depth;
};



extern void huffman_encoding_tree(char fileName[], struct huffman_heap* tree);
extern struct huffman_node* create_node(struct huffman_heap* tree, char ch);
extern int in_tree(struct huffman_heap *tree, char ch);
extern int from_tree(struct huffman_heap *tree, char code[]);
extern struct huffman_node* insert_value(struct huffman_heap* tree, char ch, int index);
extern int print_data(struct huffman_heap* tree, char fileName[]);
extern void make_heap(struct huffman_heap* tree);
extern void heapify(struct huffman_heap *tree, int len, int i);
extern struct huffman_node* delete_heap(struct huffman_heap* tree);
extern int insert_heap(struct huffman_heap* tree, struct huffman_node* left, struct huffman_node* right, int freq);
extern struct huffman_node* create_tree(struct huffman_heap* tree);
extern void variable_length_encoding(struct huffman_heap* tree, char fileName[]);
extern void constant_length_encoding(struct huffman_heap* tree, char fileName[]);
extern void traversal(struct huffman_node* node, char buf[], FILE *write_fp);


extern int send_tree(int sock, struct huffman_heap* tree, char treeReadFile[]);
extern int recv_tree(int sock, struct huffman_heap* tree, char treeWriteFile[]);
extern int extract(int i, struct huffman_node* node, char buf[]);
extern long int getFileSize(char filename[]);
extern int encode_send(int sock, struct huffman_heap* tree, char readFileName[]);
extern void encoding_traversal(struct huffman_node* node, char buf[], struct huffman_heap* newTree);
extern int recv_decode(int sock, struct huffman_heap* tree, char writeFileName[]);

#endif