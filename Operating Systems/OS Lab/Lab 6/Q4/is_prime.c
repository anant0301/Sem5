#include "../headers.h"
void * is_prime(int *num_addr)
{
	int num = *num_addr;
	if(num <= 1 || num % 2 == 0)
	{
		if (num != 2)
			return NULL;
		printf("%d ", num);
		return NULL;
	}
	for(int i = 3; i <= num / 3 ; i += 2)
	{
		if(num % i == 0)
		{
			return NULL;
		}
	}
	printf("%d ", num);
	return NULL;
}