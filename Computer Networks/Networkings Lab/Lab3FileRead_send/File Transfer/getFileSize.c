#include "headers.h"

long long int getFileSize(char filename[])
{
	FILE *fp = fopen(filename, "r");
	fseek(fp, 0L, SEEK_END);
	long long int filesize = ftell(fp);
	fclose(fp);
	return filesize;
}
