#ifndef header_q3
#define header_q3

#define MAX_STR 20
#define MAX_WORD_LEN 20
#define MAX_MEANING_LEN 20
#define MAX_DICT_LEN 20

// int BUF_SIZE = MAX_MEANING_LEN + MAX_MEANING_LEN + MAX_WORD_LEN; 

typedef struct word
{
    char word[MAX_WORD_LEN];
    char primary_meaning[MAX_MEANING_LEN];
    char secondary_meaning[MAX_MEANING_LEN];
} Word;

typedef struct node
{
    Word * block;
    struct node * left;
    struct node * right;
} Node;


#endif