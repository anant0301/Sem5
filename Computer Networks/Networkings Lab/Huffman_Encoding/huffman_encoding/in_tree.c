#include "../headers.h"
int in_tree(struct huffman_heap *tree, char ch)
{
    struct huffman_node* node;
    for(int i = 0; i < tree-> length; ++i)
    {
        node = tree-> arr[i];
        if(node-> data == ch)
        {
            return i;
        }
    }
    return -1;
}