#include "headers.h"

int encode_send(int sock, struct huffman_heap* tree, char readFileName[])
{
    FILE *read_fp = fopen(readFileName, "r");
    char buf[BUFFER_SIZE];
    char send_buf[BUFFER_SIZE] = "\0";
    int index;
    int length;
    long unsigned int lengthSent = 0;
    printf("File size: ");
    long unsigned int fileSize = getFileSize(readFileName);
    sprintf(buf, "%ld\n", fileSize);
    send(sock, buf, BUFFER_SIZE, 0);
    bzero(buf, BUFFER_SIZE);
    while(fgets(buf, BUFFER_SIZE / 10, read_fp) != NULL)
    {
        // printf("%s  ", buf);
        length = strlen(buf);
        lengthSent += length;
        for(int i = 0; i < length; ++i)
        {
            index = in_tree(tree, buf[i]);
            strcat(send_buf, tree-> arr[index]-> code);
            strcat(send_buf, " ");
        }
        send(sock, send_buf, BUFFER_SIZE, 0);
        // printf("%s\n", send_buf);
        bzero(buf, BUFFER_SIZE);
        bzero(send_buf, BUFFER_SIZE);
    }
    fclose(read_fp);
    printf("%s\n", buf);
    return 1;
}