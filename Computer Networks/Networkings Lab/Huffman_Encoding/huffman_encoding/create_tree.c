#include "../headers.h"
struct huffman_node* create_tree(struct huffman_heap* tree)
{
    struct huffman_node* root = NULL;
    struct huffman_node* l_node = NULL;
    struct huffman_node* r_node = NULL;
    do{
        l_node = delete_heap(tree);
        r_node = delete_heap(tree);
        insert_heap(tree, l_node, r_node, l_node-> freq + r_node-> freq);
        // for (int i = 0; i < tree-> length; i++)
        // {
        //     if(tree-> arr[i]-> left_)
        //         printf("%c %d %s\n", tree-> arr[i]-> left_-> data, tree-> arr[i]-> left_-> freq, tree-> arr[i]-> left_-> code);
        //     if(tree-> arr[i]-> right_)
        //         printf("%c %d %s\n", tree-> arr[i]-> right_-> data, tree-> arr[i]-> right_-> freq, tree-> arr[i]-> right_-> code);
        //     // traversal(tree->arr[i], "|");
        // }
    }while(tree-> length != 1);
    root = tree-> arr[0];
    return root;
}