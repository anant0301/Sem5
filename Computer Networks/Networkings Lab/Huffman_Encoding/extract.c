#include "headers.h"
int extract(int index, struct huffman_node* node, char buf[])
{
    int i;
    for (i = 0; buf[i] != ' '; i++)
    {
        node-> code[i] = buf[i];
    }
    node-> code[i + 1] == '\0';
    // printf("node code= %s.......", node-> code);
    if(buf[i + 1] == ' ' && buf[i + 2] != ' ')
    {
        node-> data = '\n';
    }
    else
    {
        node-> data = buf[i + 1];
    }
    i += 2;
    // printf("node data= %c\n", node-> data);   
    node-> freq = atoi(&buf[i]);
    // printf("node freq= %d\n", node-> freq);
    
    if(index ==  atoi(node-> code))
    {
        return 1;
    }
    else
    {
        return 0;
    }
}