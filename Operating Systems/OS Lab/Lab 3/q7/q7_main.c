#include "headers.h"
int main(int argc, const char *argv[])
{
	int len;
	char lName[] = "l_tmp.txt";
	char uName[] = "u_tmp.txt";
	int l_limit;
	int u_limit;
	FILE *fp;
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
		pid_t pid;
		while((pid = fork()) < 0)
		{
			printf("Fork Failed\n");
		}
		if(pid == 0)
		{
			lower_bound(x, arr, 0, r_value + 1, lName);
			fp = fopen(lName, "r");
			while(fscanf(fp, "%d\n", &l_limit) >= 0)
			{
				if(l_limit < r_value)
					r_value = l_limit;
			}
			printf("Lower Limit: %d\n", r_value);
		}
		else
		{
			upper_bound(x, arr, r_value - 1, len, uName);
			fp = fopen(uName, "r");
			while(fscanf(fp, "%d\n", &u_limit) >= 0)
			{
				if(u_limit > r_value)
					r_value = u_limit;
			}
			printf("Upper Limit: %d\n", r_value);
		}
		fclose(fp);
	}
	else
	{
		printf("Element not found\n");
	}
	return 0;
}
