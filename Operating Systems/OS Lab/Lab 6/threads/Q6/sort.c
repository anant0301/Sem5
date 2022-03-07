#include "../headers.h"
#include "header_q6.h"
void *sort(void *q6_)
{
	struct q6_main* temp = (struct q6_main*) q6_;
	int len = temp-> len;
	int *arr = temp-> arr;
	int dsc = temp-> dsc;
	int f;
	for(int j = 1; j < len; ++j)
	{
		for(int i = 0; i < j; ++i)
		{
			f = arr[j] < arr[i];
			if((!dsc && f) || (!f && dsc))
			{
				arr[i] = arr[j] ^ arr[i];
				arr[j] = arr[j] ^ arr[i];
				arr[i] = arr[j] ^ arr[i];
			}
		}
	}
	printf("Dsc = %d\n", dsc);
	for (int i = 0; i < len; ++i)
	{
		printf("%d ", arr[i]);
	}
	printf("\n");
	return NULL;
}