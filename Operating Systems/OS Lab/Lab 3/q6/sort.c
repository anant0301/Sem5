int sort(int arr[], int len,  int compare(int,  int))
{
	for(int j = 1; j < len; ++j)
	{
		for(int i = 0; i < j; ++i)
		{
			if(compare(arr[i], arr[j]))
			{
				arr[i] = arr[j] ^ arr[i];
				arr[j] = arr[j] ^ arr[i];
				arr[i] = arr[j] ^ arr[i];
			}
		}
	}
	return 0;
}