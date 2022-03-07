#include "../headers.h"
#include "header_q7.h"
extern int upper_bound(void * param);
extern int lower_bound(void * param);
extern void random_fill(int arr[], int len);
extern int binary_search(int x, int arr[], int beg, int end);
int main(int argc, const char *argv[])
{
	int len;
	int x;
	len = atoi(argv[1]);
	int arr[len];
	random_fill(arr, len);
	printf("Format::(index, value)\n");
	for (int i = 0; i < len; ++i)
	{
		// arr[i] =  atoi(argv[i + 1]);
		printf("(%d, %d) ", i, arr[i]);
	}
	printf("\nEnter the element you want to find in the array: ");
	scanf("%d", &x);
	int r_value = binary_search(x, arr, 0, len);
	if(r_value != -1)
	{
		struct q7_main *low = (struct q7_main*)malloc(sizeof(struct q7_main));
		struct q7_main *up = (struct q7_main*)malloc(sizeof(struct q7_main));
		pthread_attr_t attr;
		pthread_t tid_l;
		pthread_t tid_u;
		int l_limit;
		int u_limit;
		up-> end = len;
		low-> beg = 0;
		low-> x = up-> x = x;
		up-> beg = low-> end = r_value;
		up-> arr = low-> arr = arr;
		pthread_attr_init(&attr);
		pthread_create(&tid_l, &attr, lower_bound, low);
		pthread_create(&tid_u, &attr, upper_bound, up);
		pthread_join(tid_l, &l_limit);
		pthread_join(tid_u, &u_limit);
		printf("%d %d\n", l_limit, u_limit);
	}
	else
	{
		printf("Element not found\n");
	}
	return 0;
}
