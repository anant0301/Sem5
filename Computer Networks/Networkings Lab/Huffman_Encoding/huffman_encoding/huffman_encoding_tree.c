#include "../headers.h"
void huffman_encoding_tree(char fileName[], struct huffman_heap* tree)
{
    char file_read_buffer[BUFFER_SIZE];
    int index = -1;
    FILE *read_fp = fopen(fileName, "r");
    if(read_fp == NULL)
    {
        printf("File open failure\n");
        exit(1);
    }
    tree-> arr = calloc(sizeof(struct huffman_node*), MAX_TREE_SIZE);
    while(fgets(file_read_buffer, BUFFER_SIZE, read_fp))
    {
        for (int i = 0; i < strlen(file_read_buffer); i++)
        {
            if((index = in_tree(tree, file_read_buffer[i])) == -1)
            {
                // printf("%d\n", i);
               tree-> arr[tree-> length] = create_node(tree, file_read_buffer[i]);
            }
            else
            {
                // printf("%c not present in tree\n", file_read_buffer[i]);
                tree-> arr[index]-> freq++;
            }
        }
    }
}