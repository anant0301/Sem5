#include "headers.h"
int main(int argc, char * argv[])
{
    Router * r = malloc(sizeof(Router));
    init();
    init_router(&r);
    printf("This is the routing table\n");
    for (int i = 0; i < MAX_DEVICES; i++)
    {
        for (int j = 0; j < MAX_DEVICES; j++)
        {
            printf("%d\t", conn_matrix[j][i]);
        }
        printf("\n");
    }
    return 0;
}