#include "../headers.h"
void constant_length_encoding(struct huffman_heap* tree, char fileName[])
{
    FILE *write_fp = fopen(fileName, "w");
    char buf[BUFFER_SIZE];
    if(write_fp == NULL)
    {
        printf("File Write Failed\n");
        exit(1);
    }
    fprintf(write_fp, "%d\n", tree-> length);
     for (int i = 0; i < tree-> length; i++)
    {
        if(tree-> arr[i]-> data == '\n')
        {
            fprintf(write_fp, "%s  %d\n", tree-> arr[i]-> code, tree-> arr[i]-> freq);
            continue;
        }
        fprintf(write_fp, "%s %c %d\n", tree-> arr[i]-> code, tree-> arr[i]-> data, tree-> arr[i]-> freq);
    }
    fclose(write_fp);   
}