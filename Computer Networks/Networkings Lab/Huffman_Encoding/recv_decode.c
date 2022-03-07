#include "headers.h"

int recv_decode(int sock, struct huffman_heap* tree, char writeFileName[])
{
    FILE *write_fp = fopen(writeFileName, "w");
    char buf[BUFFER_SIZE];
    char temp_buf[BUFFER_SIZE];
    char send_buf[BUFFER_SIZE];
    char write_buf[BUFFER_SIZE];
    int index;
    int nb;
    long int fileSize;
    recv(sock, buf, BUFFER_SIZE, 0);
    printf("File Size: %ld", fileSize);
    printf("File Size: %s", buf);
    sscanf(buf, "%ld\n", &fileSize);
    bzero(buf, BUFFER_SIZE);
    bzero(write_buf, BUFFER_SIZE);
    bzero(temp_buf, BUFFER_SIZE);
        while(recv(sock, buf, BUFFER_SIZE, 0) > 0){
        nb = 0;
        for (int i = 0, j = 0; i < strlen(buf); i++)
        {
            if(buf[i] == ' ')
            {
                index = from_tree(tree, temp_buf);
                if(index == -1)
                {
                    printf("%s\n", buf);
                }
                write_buf[nb++] = tree-> arr[index]-> data;
                j = 0;
                bzero(temp_buf,BUFFER_SIZE);
            }
            temp_buf[j++] = buf[i];
        }
        
        fputs(write_buf, write_fp);
        fileSize -= nb;
        bzero(buf, BUFFER_SIZE);
        bzero(write_buf, BUFFER_SIZE);
        bzero(temp_buf, BUFFER_SIZE);
    }
    return 1;
}