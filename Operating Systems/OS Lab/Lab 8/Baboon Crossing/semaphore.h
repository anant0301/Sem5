#pragma once

#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/sem.h>
#include <fcntl.h>
#include <semaphore.h>

#define DIR "/direction"
#define ROPE_SEMA "/rope_sem"
#define ROPE_LIMIT 3

void control();
void * crossover(void *);

sem_t * direction;
sem_t * rope_sem;
int b_count;
pthread_t baboon_on_rope[ROPE_LIMIT];