#include "../headers.h"
struct huffman_node* create_node(struct huffman_heap* tree, char ch)
{
    struct huffman_node *node = (struct huffman_node*)malloc(sizeof(struct huffman_node));
    node-> data = ch;
    node-> freq = 1;
    node-> left_ = NULL;
    node-> right_ = NULL;
    bzero(node-> code, MAX_ENCODE_LEN);
    tree-> length++; 
    return node;
}