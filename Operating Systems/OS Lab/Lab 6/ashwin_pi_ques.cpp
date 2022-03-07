#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define NUM_THREADS 8
#define TOTAL_COUNT 10000055

float randNumGen()
{
	int random_value = rand();
	float unit_random = random_value / (float)RAND_MAX;
	return unit_random;
}

void *Calculation(void *threadid)
{
	long longTid;
	longTid = (long)threadid;

	int tid = (int)longTid;

	float *in_count = (float *)malloc(sizeof(float));
	*in_count = 0;

	float total_iterations = TOTAL_COUNT / NUM_THREADS;

	int counter = 0;

	for (counter = 0; counter < total_iterations; counter++)
	{
		float x = randNumGen();
		float y = randNumGen();

		float result = sqrt((x * x) + (y * y));

		if (result < 1)
		{
			//check if the generated value is inside a unit circle
			*in_count += 1;
		}
	}

	//get the remaining iterations calculated by thread 0
	if (tid == 0)
	{
		float remainder = TOTAL_COUNT % NUM_THREADS;

		for (counter = 0; counter < remainder; counter++)
		{
			float x = randNumGen();
			float y = randNumGen();

			float result = sqrt((x * x) + (y * y));

			if (result < 1)
			{
				//check if the generated value is inside a unit circle
				*in_count += 1;
			}
		}
	}
	pthread_exit((void *)in_count); 
}

int main(int argc, char *argv[])
{
	pthread_t threads[NUM_THREADS];
	int rc;
	long t;
	void *status;
	float tot_in = 0;

	for (t = 0; t < NUM_THREADS; t++)
	{
		rc = pthread_create(&threads[t], NULL, Calculation, (void *)t);
		if (rc)
		{
			printf("ERROR; return code from pthread_create() is %d\n", rc);
			exit(-1);
		}
	}

	for (t = 0; t < NUM_THREADS; t++)
	{
		pthread_join(threads[t], &status);
		tot_in += *(float *)status; //keep track of the total in count
	}
	printf("Value for Pi is %f \n", 4 * (tot_in / TOTAL_COUNT));
	pthread_exit(NULL);
}