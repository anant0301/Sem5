#include "../headers.h"
void make_heap(struct huffman_heap* tree)
{
    /*MIN HEAP*/
    for(int i = tree-> length / 2 - 1; i >= 0; --i)
    {
        heapify(tree, tree-> length,  i);
    }
}