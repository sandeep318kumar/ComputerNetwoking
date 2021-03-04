#include <iostream>
#include <string.h>
#include <stdio.h> 
#include <unistd.h> 
#include <fcntl.h> 
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <poll.h>
#include <signal.h>
#include <dirent.h>
#include <wait.h> 
#include <sys/wait.h>
#include <sys/stat.h> 
#include <sys/types.h>
#include <sys/mman.h>
#include <sys/resource.h>
#include <sys/msg.h>
#include <sys/uio.h>
#include<sys/shm.h>

using namespace std;

void die(char *s)
{
  perror(s);
  exit(1);
}


int main()
{
	sem_t *s23 = sem_open("/s23", O_CREAT | O_RDWR, 0660, 0);
    sem_t *s43 = sem_open("/s43", O_CREAT | O_RDWR, 0660, 0);

	sem_t *A2 = sem_open("/a2", O_CREAT | O_RDWR, 0660, 0);
    sem_t *A1 = sem_open("/a1", O_CREAT | O_RDWR, 0660, 0);

	while(1){
		// checking for signal
		sem_wait(A2);
		sleep(1);
		sem_post(s12);
		
		// given access to c2
		sem_post(A3);
		sem_wait(s23);
	}

    return 0;
}