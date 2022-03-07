#include "headers.h"
int mergeBack(int arr[], int begin, int mid, int end, char fileName[])
{
	/*	merge two arrays in a sorted order and write to a file named in fileName	*/
	/*	the array pointer whose elements will be written to file*/
	/*	the array is divided by mid	*/
	/*	left--> arr[begin..mid-1]	*/
	/*	right--> arr[mid..end]	*/
	int p1 = begin;
	int p2 = mid;
	FILE *fp = fopen(fileName, "w");
	while(p1 < mid && p2 < end)
	{
		if(arr[p1] > arr[p2])
		{
			fprintf(fp, "%d ", arr[p2]);
			p2++;
		}
		else
		{
			fprintf(fp, "%d ", arr[p1]);
			p1++;
		}
	}
	/*	write the rest of the elements to the file	*/
	while(p1 < mid)
	{
		fprintf(fp, "%d ", arr[p1]);	
		p1++;
	}
	/*	write the rest of the elements to the file	*/
	while(p2 < end)
	{
		fprintf(fp, "%d ", arr[p2]);
		p2++;
	}
	fclose(fp);
	return 0;
}