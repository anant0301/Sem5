#include "headers.h"

int main(int argc, char *argv[])
{
    int len = atoi(argv[1]);
    int arr[len];
    randomfill(arr, len);
    for (int i = 0; i < len; i++)
    {
        printf("%d ", arr[i]);
    }
    printf("\n");
    
    qSort(arr, 0, len - 1, arr[len / 2]);

    return 0;
}