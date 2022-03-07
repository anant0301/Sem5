#include "headers.h"

int main(int argc, char const *argv[])
{
	int len;
	char input[IN_STRING_LENGTH];
	int in_len;
	char uniq[IN_STRING_LENGTH];
	pid_t pid;
	char fileName[] = "temp_file.txt";
	FILE *fp = fopen(fileName, "w");
	int count;

	fgets(input, IN_STRING_LENGTH, stdin);
	in_len = strlen(input);
	len = uniq_element(input, uniq, in_len);
	for(int i = 0; i < len; ++i)
	{
		while((pid = fork()) < 0)
		{
			printf("Fork Failed\n");
		}
		if(pid == 0)
		{
			count = linear_search(input, uniq[i], in_len);
			fprintf(fp, "\t\t|\n");
			fprintf(fp, "'%c'\t\t|", uniq[i]);
			for(int j = 0; j < count;++j)
				fprintf(fp, "=");
			fprintf(fp, "%d\n\t\t|\n", count);
			fclose(fp);
			exit(1);
		}
	}

	fclose(fp);
	while((pid = wait(NULL)) > 0);
	fp = fopen(fileName, "r");
	char buf[BUFSIZ];
	while(fgets(buf, BUFSIZ, fp))
	{
		printf("%s", buf);
	}
	fclose(fp);
	
	return 0;
}