#include "../headers.h"
#include "header_q7_1.h"
extern void * binary_search(void * param);
extern void random_fill(int arr[], int len);
int main(int argc, char  *argv[])
{
    int len = atoi(argv[1]);
    int arr[len];
    random_fill(arr, len);// - 200);
    // for(int i = len - 200; i < len;++i)
    // {
    //     arr[i] = arr[len - 200 - 1];
    // }
    for (int i = 0; i < len; i++)
    {
        printf("(%d, %d )", i, arr[i]);
    }
    printf("\n");
    int x;
    scanf("%d", &x);
    struct q7_main * init = (struct q7_main*)malloc(sizeof(struct q7_main));
    init-> arr = arr;
    init-> beg = 0;
    init-> end = len - 1;
    init-> side = 'i';
    init-> x = x;
    init-> index = -1;
    binary_search(init);
    if (init-> index != -1)
    {
        printf("Range of Elements: %d %d\n", init-> beg, init-> end);
    }
    else
    {
        printf("Element not present\n");
    }
    return 0;
}