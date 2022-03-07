#include "../headers.h"
#include "header_q4.h"
Node * insert(Node * root, Word * new)
{
    if(root == NULL)
    {
        root = (Node * )malloc(sizeof(Node));
        root-> block = new;
        root-> left = root-> right = NULL;
    }
    else
    {
        int x = strcmp(root-> block-> word, new-> word);
        if (x < 0)
        {
            root-> left = insert(root-> left, new);
        }
        else if(x > 0)
        {
            root-> right = insert(root-> right, new);
        }
        else 
        {
            printf("%s: Word already present\n", new-> word);
        }
    }
    return root;
}

Node * search(Node * root, char word[])
{
    Node * return_value = NULL;
    if(root != NULL)
    {
        int comp = strcmp(root-> block-> word, word);
        if (comp < 0)
        {
            return_value = search(root-> left, word);
        }
        else if (comp > 0)
        {
            return_value = search(root-> right, word);
        }
        else
        {
            return_value = root;
        }
    }
    else
    {
        printf("%s not in the dictionary\n", word);
    }
    return return_value;
}