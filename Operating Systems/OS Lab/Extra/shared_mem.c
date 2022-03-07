#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/shm.h>	
#include <sys/wait.h>
int main()
{
	int shmid, status;
	int * ptr;
	int pid;
	// create a memory for with same size as int and keep the variable to the parent and its child
	shmid = shmget(IPC_PRIVATE, sizeof(int), 0777|IPC_CREAT);
	if ((pid = fork()) == 0) {
		ptr = (int *) shmat(shmid, 0, 0);
		/*
		there needs to synchronization between the process when altering the memory 
		but with this setup the memory for the variable is now shared by the 2 child processes  
		*/
		*ptr = 101;
		shmdt(ptr);
		exit(1);
	}
	else {

		if (fork () == 0)
		{
			ptr = (int *) shmat(shmid, 0, 0);
			/*
			there needs to synchronization between the process when altering the memory 
			but with this setup the memory for the variable is now shared by the 2 child processes  
			*/
			waitpid(pid, 0, 1);
			printf("variable value is %d\n", *ptr);
			shmdt(ptr);
		}

		wait(&status);
		shmctl(shmid, IPC_RMID, 0);
	}
}

