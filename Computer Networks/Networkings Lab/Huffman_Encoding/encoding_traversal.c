#include "headers.h"
void encoding_traversal(struct huffman_node* node, char buf[], struct huffman_heap* newTree)
{
    if(node-> left_ == NULL && node-> right_ == NULL)
    {
        int length = newTree-> length;
        newTree-> arr[length] = create_node(newTree, node-> data);
        strcpy(newTree-> arr[length]-> code, node-> code);
        newTree-> arr[length]-> data = node-> data;
        return ;       
    }
   
    encoding_traversal(node-> left_, node-> left_-> code, newTree);
    encoding_traversal(node-> right_, node-> right_-> code, newTree);
}