#include "../headers.h"
int print_data(struct huffman_heap* tree, char fileName[])
{
    FILE *write_fp = fopen(fileName, "w");

    for(int i = 0; i < tree-> length; ++i)
    {
        fprintf(write_fp, "%c %.3x \n", tree-> arr[i]-> data, tree-> arr[i]-> freq);
    }
    printf("\n");
    return 1;
}