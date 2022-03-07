#include "../headers.h"
struct huffman_node* delete_heap(struct huffman_heap* tree)
{    
    struct huffman_node* node = tree-> arr[0];
    tree-> arr[tree-> length] = tree-> arr[0];
    tree-> arr[0] = tree-> arr[--tree-> length];
    heapify(tree, tree-> length, 0);
    return tree-> arr[tree-> length + 1];
}