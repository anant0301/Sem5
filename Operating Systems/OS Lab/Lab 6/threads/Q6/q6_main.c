#include"../headers.h"
#include "header_q6.h"
extern void *sort(void *q6_);

int main(int argc, char const *argv[])
{
	printf("The given arguments will be sorted...\n");
	int len = argc - 1;
	int arr_asc[len];
	int arr_dsc[len];
	pthread_t tid_asc;
	pthread_t tid_dsc;
	for (int i = 0; i < len; ++i)
	{
		arr_dsc[i] = atoi(argv[i + 1]);
		arr_asc[i] = atoi(argv[i + 1]);
	}
	struct q6_main* q6_asc = (struct q6_main*)malloc(sizeof(struct q6_main));
	struct q6_main* q6_dsc = (struct q6_main*)malloc(sizeof(struct q6_main));
	q6_asc-> len = q6_dsc-> len = len;
	q6_dsc-> arr = arr_dsc;
	q6_asc-> arr = arr_asc;
	q6_dsc-> dsc = 1;
	q6_asc-> dsc = 0;
	pthread_create(&tid_asc, NULL, sort, q6_asc);
	pthread_create(&tid_dsc, NULL, sort, q6_dsc);

	pthread_join(tid_asc, NULL);
	pthread_join(tid_dsc, NULL);
	return 0;
}
