#include "../headers.h"
#include "header_q9.h"
extern void * longest_common_subsequence(void * param);
int main(int argc, char *argv[])
{
    char str_1[MAX_STR_LEN] = "The str_1 given"; 
    char str_2[MAX_STR_LEN] = "The string givwn"; 
    struct q9_main *init = (struct q9_main*)malloc(sizeof(struct q9_main));
    init-> str_1 = str_1;
    init-> str_2 = str_2;
    init-> len_lcs = init-> n_str_1 = init-> n_str_2 = 0;
    init-> len_str_1 = strlen(str_1);
    init-> len_str_2 = strlen(str_2);
    printf("String 1:\t%s\n", str_1);
    printf("String 2:\t%s\n", str_2);
    printf("length of string 1: %d\n", init-> len_str_1);
    printf("length of string 2: %d\n", init-> len_str_2);
    longest_common_subsequence(init);
    printf("Subsequence Length: %d\nSubsequence: %s\n", init-> len_lcs, init-> lcs);
    return 0;
}