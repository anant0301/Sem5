#include "../headers.h"
void traversal(struct huffman_node* node, char buf[], FILE *write_fp)
{
 
    if(node-> left_ == NULL && node-> right_ == NULL)
    {
        if(node-> data != '\n')
        {
            fprintf(write_fp, "%s %c %d\n", node-> code, node-> data, node-> freq);
            // printf("node->code = %s char= %c\n", node-> code, node->data);
        }
        else
        {
            fprintf(write_fp, "%s  %d\n", node-> code, node-> freq);
            // printf("node->code = %s char= %c\n", node-> code, node->data);
        }
            
        return ;
    }
    char one[] = "1";
    char zero[] = "0";
    strcat(node-> left_-> code, buf);
    strcat(node-> right_-> code, buf);
    strcat(node-> left_-> code, zero);
    strcat(node-> right_-> code, one);
    traversal(node-> left_, node-> left_-> code, write_fp);
    traversal(node-> right_, node-> right_-> code, write_fp);
}