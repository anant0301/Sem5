#include "headers.h"
int lower_bound(int x, int arr[], int beg, int end, char fileName[])
{
	FILE *fp = fopen(fileName, "w");
	int r_value = binary_search(x, arr, beg, end);
	while(beg <= end && r_value != -1)
	{
		end = r_value - 1; 
		fprintf(fp, "%d\n", r_value);
		r_value = binary_search(x, arr, beg, end);
	}
	fclose(fp);
	return r_value;
}
