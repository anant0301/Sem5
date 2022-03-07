#include "../headers.h"
int get_sum(void* num)
{
	
	int *num_ = (int *)num;
	int n = *num_;
	int sum = 0;
	int temp;
	while(n != 0)
	{
		temp = (n % 10);
		sum += temp * temp * temp;
		n /= 10;
	}
	return sum;
}