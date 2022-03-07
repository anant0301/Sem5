#include "headers.h"
int recv_tree(int sock, struct huffman_heap* tree, char treeWriteFile[])
{
    
    char buf[BUFFER_SIZE];
    int length;
    int i;
    int nb;
    FILE *write_fp = fopen(treeWriteFile, "w");
    nb = recv(sock, buf, BUFFER_SIZE, 0);
    sscanf(buf, "%d\n", &(length));
    fputs(buf, write_fp);
    printf("Size of tree: %d\n", length);
    bzero(buf, BUFFER_SIZE);
    tree-> arr = calloc(sizeof(struct huffman_node*), length);
    // printf("Contents of the tree are as follows\n");
    for (i = 0; i < length; i++)
    {
        bzero(buf, BUFFER_SIZE);
        nb = recv(sock, buf, BUFFER_SIZE, 0);
        if(nb == -1)
        {
            perror("File recv Error");
        }
        fputs(buf, write_fp);
        tree-> arr[tree-> length] = create_node(tree, 0);
        extract(i, tree-> arr[i], buf);
        // printf("Code: %s \tChar: %c \tFreq: %d\n", tree-> arr[i]-> code, tree-> arr[i]-> data, tree-> arr[i]-> freq);
    }
    fclose(write_fp);
    return 1;
}