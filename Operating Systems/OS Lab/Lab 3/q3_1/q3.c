#include "headers.h"
int main(int argc, char  *argv[])
{
	int m = atoi(argv[1]);
	int n = atoi(argv[2]);
	for(int i = (m < n ? m : n); i < (n < m ? m : n); i++)
	{
		if(is_armstrong(i))
		{
			printf("Armstrong Number %d \n", i);
		}
	}
	return 0;
}
