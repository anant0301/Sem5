#include "headers.h"
long long int getFileSize(char filename[])
{
	struct stat st;
	stat(filename, &st);
	printf("%s: %ld\n", filename, st.st_size);
	return st.st_size;
}