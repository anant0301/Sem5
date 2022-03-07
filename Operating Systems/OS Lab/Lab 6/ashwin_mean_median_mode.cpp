#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include <math.h>
#include <pthread.h>
#include <string.h>

struct node
{
    int *elements;
    float mean;
    float median;
    int mode;
    int size;
};

int cmpfunc(const void *a, const void *b)
{
    return (*(int *)a - *(int *)b);
}

void *mean(void *arg)
{
    int sum = 0;
    struct node *temp = ((struct node *)arg);
    for (int i = 0; i < temp->size; i++)
    {
        sum += temp->elements[i];
    }
    temp->mean = float(sum) / float(temp->size);
    pthread_exit(NULL);
}

void *median(void *arg)
{
    struct node *temp = ((struct node *)arg);
    int *a = temp->elements;
    qsort(a, temp->size, sizeof(int), cmpfunc);
    if (temp->size % 2 == 0)
    {
        temp->median = ((float)a[temp->size / 2] + (float)a[(temp->size / 2) - 1]) / 2;
    }
    else
        temp->median = a[temp->size / 2];

    pthread_exit(NULL);
}

void *mode(void *arg)
{
    struct node *temp = ((struct node *)arg);
    int *a = temp->elements;

    qsort(a, temp->size, sizeof(int), cmpfunc);
    int count1 = 1, count2 = 1;
    int i = 0, index = 1;
    int mo = a[0];

    for (i = 0; i < temp->size; i++)
    {
        if (a[i] == a[i + 1])
        {
            while (a[i] == a[i + 1])
            {
                count1++;
                i++;
            }
            if (count1 > count2)
            {
                count2 = count1;
                mo = a[i];
                count1 = 1;
            }
        }
    }
    temp->mode = mo;

    pthread_exit(NULL);
}

void process(struct node *temp)
{
    pthread_t pth[3];

    pthread_create(&pth[0], NULL, mean, temp);
    pthread_create(&pth[1], NULL, median, temp);
    pthread_create(&pth[2], NULL, mode, temp);
    pthread_join(pth[0], NULL);
    pthread_join(pth[1], NULL);
    pthread_join(pth[2], NULL);

    printf("\nMEAN: %f\nMEDIAN: %f\nMODE: %d\n", temp->mean, temp->median, temp->mode);
}

int main()
{
    struct node *result = (struct node *)malloc(sizeof(struct node));
    printf("Enter the no. of elements: ");
    scanf("%d", &result->size);
    result->elements = new int[result->size];

    printf("Enter the elements: ");
    for (int i = 0; i < result->size; i++)
        scanf("%d", &result->elements[i]);
    process(result);
    return 0;
}