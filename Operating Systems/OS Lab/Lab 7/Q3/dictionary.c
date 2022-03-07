#include "../headers.h"
#include "header_q3.h"
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
        if (strcmp(root-> block-> word, new-> word) < 0)
        {
            root-> left = insert(root-> left, new);
        }
        else
        {
            root-> right = insert(root-> right, new);
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