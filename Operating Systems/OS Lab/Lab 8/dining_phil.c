#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <stdlib.h>

#define NUM_PHIL 5

void *philosopher(void *);
void think(int);
void pickUp(int);
void eat(int);
void putDown(int);

pthread_mutex_t spoon[NUM_PHIL];
pthread_t philosophers[NUM_PHIL];

int main() 
{
	int i;
	srand(time(NULL));
	for (i = 0; i < NUM_PHIL; ++i) 
    {
		pthread_mutex_init(&spoon[i], NULL);
		pthread_create(&philosophers[i], NULL, philosopher, (void *)(i));
	}

	for (i = 0; i < NUM_PHIL; ++i) 
    {
		pthread_join(philosophers[i], NULL);
	}
	return 0;
}

void *philosopher(void *phil_num) 
{
	while (1) 
    {
		think(phil_num);
		pickUp(phil_num);
		eat(phil_num);
		putDown(phil_num);
	}
}

void think(int phil_num) 
{
	int sleepTime = rand() % (NUM_PHIL - 1) + 1;
	printf("Philosopher %d will think for %d seconds\n", phil_num, sleepTime);
	sleep(sleepTime);
}

void pickUp(int phil_num) 
{
	int right = (phil_num + 1) % NUM_PHIL;
	int left = (phil_num + NUM_PHIL) % NUM_PHIL;
	if (phil_num & 1) // phil_num is odd 
    {
		printf("Philosopher %d is waiting to pick up chopstick %d\n", phil_num, right);
		pthread_mutex_lock(&spoon[right]);
		printf("Philosopher %d picked up chopstick %d\n", phil_num, right);
		printf("Philosopher %d is waiting to pick up chopstick %d\n", phil_num, left);
		pthread_mutex_lock(&spoon[left]);
		printf("Philosopher %d picked up chopstick %d\n", phil_num, left);
	}
	else 
    {
		printf("Philosopher %d is waiting to pick up chopstick %d\n", phil_num, left);
		pthread_mutex_lock(&spoon[left]);
		printf("Philosopher %d picked up chopstick %d\n", phil_num, left);
		printf("Philosopher %d is waiting to pick up chopstick %d\n", phil_num, right);
		pthread_mutex_lock(&spoon[right]);
		printf("Philosopher %d picked up chopstick %d\n", phil_num, right);
	}
}

void eat(int phil_num) 
{
	int eatTime = rand() % 3 + 1;
	printf("Philosopher %d will eat for %d seconds\n", phil_num, eatTime);
	sleep(eatTime);
}

void putDown(int phil_num) 
{
	printf("Philosopher %d will will put down the spoon\n", phil_num);
	pthread_mutex_unlock(&spoon[(phil_num + 1) % NUM_PHIL]);
	pthread_mutex_unlock(&spoon[(phil_num + NUM_PHIL) % NUM_PHIL]);
}