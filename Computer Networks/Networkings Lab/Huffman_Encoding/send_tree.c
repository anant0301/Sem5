#include "headers.h"
int send_tree(int sock, struct huffman_heap* tree, char treeReadFile[])
{
    char buf[BUFFER_SIZE];
    struct huffman_node* node;
    int length;
    int nb;
    FILE *read_fp = fopen(treeReadFile, "r");
    fgets(buf, BUFFER_SIZE, read_fp);
    nb = send(sock, buf, BUFFER_SIZE, 0);
    sscanf(buf, "%d\n", &length);
    printf("Length of tree: %d\n", length);
    while(fgets(buf, BUFFER_SIZE, read_fp) != NULL)
    {
        nb = send(sock, buf, BUFFER_SIZE, 0);
        if(nb == -1)
        {
            perror("File send Error");
        }
        // printf("%s", buf);
        bzero(buf, BUFFER_SIZE);
    }
    fclose(read_fp);
    return 1;
}