#include "../headers.h"
#include "header_q7.h"
extern int binary_search(int x, int arr[], int beg, int end);
int lower_bound(void * param)
{
	struct q7_main *temp = (struct q7_main*) param;
	int x = temp-> x;
	int beg = temp-> beg;
	int end = temp-> end;
	int *arr = temp-> arr;
	int temp_int = binary_search(x, arr, beg, end);
	int r_value;
	while(beg <= end && temp_int != -1)
	{
		r_value = temp_int;
		end = r_value - 1; 
		temp_int = binary_search(x, arr, beg, end);
	}
	return r_value;
}
