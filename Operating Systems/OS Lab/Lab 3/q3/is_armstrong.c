#include"headers.h"
int is_armstrong(int num)
{
	int n = num;
	int sum = 0;
	int temp;
	while(sum <= num && n != 0)
	{
		temp = (n % 10);
		sum += temp * temp * temp;
		n /= 10;
	}
	if(sum == num && n == 0)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}
