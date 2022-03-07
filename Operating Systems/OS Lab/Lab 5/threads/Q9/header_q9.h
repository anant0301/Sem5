#ifndef header_q9
#define header_q9
#include <string.h>

#define MAX_STR_LEN 100
struct q9_main 
{
    char *str_1;
    char *str_2;
    char lcs[MAX_STR_LEN];
    int len_str_1;
    int n_str_1;
    int len_str_2;
    int n_str_2;
    int len_lcs;
};

#endif