#include "../headers.h"
int from_tree(struct huffman_heap *tree, char code[])
{
    struct huffman_node* node;
    for(int i = 0; i < tree-> length; ++i)
    {
        node = tree-> arr[i];
        if(atoi(node-> code) == atoi(code))
        {
            return i;
        }
    }
    return -1;
}