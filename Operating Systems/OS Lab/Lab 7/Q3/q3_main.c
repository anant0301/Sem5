#include "../headers.h"
#include "header_q3.h"

extern Node * insert(Node * root, Word * new);
extern Node * search(Node * root, char word[]);
void * insertion(void * param);

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER; 

Node * root;
int main(int argc, char * argv[])
{
    char *fileName = argv[1];
    pthread_t thread;
    pthread_create(&thread, NULL, insertion, fileName);
    Node * value;
    char string[BUFSIZ];
    // consmer 
    for (int i = 97; i < 123; i++)
    {
        sprintf(string, "%c", i);
        value = search(root, string);
        if (value)
        {
            printf("The word: %s and meaning: %s %s\n", value-> block-> word, value-> block-> primary_meaning, value-> block-> secondary_meaning);
        }
        sleep(0.1);
    }
    pthread_join(thread, NULL);    
    return 0;
}

void * insertion(void * param)
{
    // producer
    char * fileName = param; 
    FILE * fp = fopen(fileName, "r");
    char buffer[BUFSIZ];
    char word[MAX_WORD_LEN];
    char pri_meaning[MAX_MEANING_LEN];
    char sec_meaning[MAX_MEANING_LEN];
    Word * new_word;
    while (fgets(buffer, BUFSIZ, fp))
    {
        sscanf(buffer, "%s %s %s", word, pri_meaning, sec_meaning);
        bzero(buffer, BUFSIZ);
        new_word = malloc(sizeof(Word));
        strcpy(new_word-> word, word);
        strcpy(new_word-> primary_meaning, pri_meaning);
        strcpy(new_word-> secondary_meaning, sec_meaning);

        bzero(word, MAX_WORD_LEN);
        bzero(pri_meaning, MAX_MEANING_LEN);
        bzero(sec_meaning, MAX_MEANING_LEN);

        pthread_mutex_lock(&mutex);
        root = insert(root, new_word);
        pthread_mutex_unlock(&mutex);

        sleep(0.1);
        // printf("%s\n", root-> block-> word);
    }
    fclose(fp);
    pthread_exit(NULL);   
}
