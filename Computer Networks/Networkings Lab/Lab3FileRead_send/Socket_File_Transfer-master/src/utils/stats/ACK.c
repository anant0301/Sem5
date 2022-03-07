#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ACK.h"
#include "../argsetup.h"

static char ACK[] = ACK_ENCODE;

extern void ACK_init(unsigned long long int *num)
{
	*num = 0;
	return;
}

extern void ACK_Set(unsigned long long int *num, char dst[], const char src[], unsigned long long int len)
{
	unsigned long long ACK_len, i;

	sprintf(dst, "%c%.20llu%c%.5llu%c%c", ACK[0], *num, ACK[ACK_NUM_MAX + 1], len, ACK[ACK_LEN - 1], '\0');

	ACK_len = strlen(dst);

	for (i = 0; i < len; i++)
		*(dst + ACK_len + i) = src[i];

	(*num)++;
}

extern void ACK_LastStep(unsigned long long int *num)
{
	if (num != NULL)
		(*num)--;
	else
		fprintf(stderr, "[error] in function ACK_LastStep: serialize number pointer is NULL.\n");
}

extern int ACK_Check(unsigned long long int *num, char src[], unsigned long long int *len)
{
	char tmp[BUF_SIZE];
	char tmp2, tmp3, tmp4;
	unsigned long long int ACK_len, ACK_num, i;

	if (num == NULL)
	{
		fprintf(stderr, "[error] in function ACK_Check: serialize number pointer is NULL.\n");
		return ACK_FAIL;
	}
	else if (src == NULL)
	{
		fprintf(stderr, "[error] in function ACK_Check: source message pointer is NULL.\n");
		return ACK_FAIL;
	}
	else if (sscanf(src, "%c%20llu%c%20llu%c", &tmp2, &ACK_num, &tmp3, &ACK_len, &tmp4) != 5)
		return ACK_FAIL;
	else if (tmp2 != ACK[0] || tmp3 != ACK[ACK_NUM_MAX + 1] || tmp4 != ACK[ACK_LEN - 1])
		return ACK_FAIL;
	/* get repeated message */
	else if (ACK_num < *num)
		return ACK_REPEAT;
	/* success */
	else if (ACK_num == *num)
	{
		if (len != NULL)
		{
			*len = ACK_len;
			for (i = 0; i < ACK_len; i++)
				tmp[i] = *(src + ACK_LEN + i);

			for (i = 0; i < ACK_len; i++)
				src[i] = tmp[i];

			src[ACK_len] = '\0';
		}
		(*num)++;

		return ACK_SUCCESS;
	}
	else
		return ACK_FAIL;
}
