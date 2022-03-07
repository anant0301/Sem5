#include "../headers.h"

int insert_heap(struct huffman_heap* tree, struct huffman_node* left, struct huffman_node* right, int freq)
{
    int len = tree-> length;

    tree-> arr[len] = create_node(tree, 0); 
    tree-> arr[len]-> freq = freq;
    tree-> arr[len]-> left_ = left;
    tree-> arr[len]-> right_ = right;
    heapify(tree, tree-> length,  tree-> length - 1);
    return 1;
}