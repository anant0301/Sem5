#include <stdio.h>
#include <time.h>

#include "log.h"

extern void printLog(unsigned long long int numerator, unsigned long long int denominator, unsigned long long int *next)
{
	char log_time_str[LOG_STRLEN_MAX];
	int flag = 0;
	time_t log_time;

	while (numerator >= (denominator / 100) * (*next + LOG_STEP) && *next < LOG_MAX)
	{
		*next += LOG_STEP;
		flag = 1;
	}

	if (flag)
	{
		time(&log_time);
		strftime(log_time_str, LOG_STRLEN_MAX - 1, "%Y/%m/%d/ %H:%M:%S", gmtime(&log_time));
		printf("%llu%% %s\n", *next, log_time_str);
	}

	return;
}

extern void resetLog(unsigned long long int *next)
{
	*next = LOG_MIN;

	return;
}

extern void printLostRate(unsigned long long int lost, unsigned long long total)
{
	printf("Loss Rate: %lf%% .\n", lost / ((double)total / 100));
}

extern void printThroughput(unsigned long long int total, clock_t interval)
{
	printf("Throughput: %lf bps .\n", total / ((double)interval / CLOCKS_PER_SEC));
}
