#include <iostream>
#include <string.h>
#include <stdio.h> 
#include <unistd.h> 
#include <fcntl.h> 
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/wait.h>
#include <unistd.h>
#include <sys/stat.h> 
#include <semaphore.h>
#include <sys/types.h>
#include <fcntl.h>
#include <poll.h>
#include <signal.h>
#include <csignal>
#include<wait.h> 
#include<signal.h> 
#include<sys/ipc.h>
#include<sys/shm.h>
#include<string.h>
using namespace std;

#define FILLED 0 
#define Ready 1 
#define NotReady -1 

struct memory { 
    char strx[100];
    char stry[100];
	int status, pid1, pid2; 
}; 

struct memory* shmptr; 

int x , y = 5;
void handler(int signum) 
{ 
	if (signum == SIGUSR1) { 
		printf("Received User2: "); 
		cout<<shmptr->stry<<endl;
        y = atoi(shmptr->stry); 
	} 
} 

int main() 
{ 
	int pid = getpid(); 
	int shmid; 
	int key = 12345; 

	shmid = shmget(key, sizeof(struct memory), IPC_CREAT | 0666); 

	shmptr = (struct memory*)shmat(shmid, NULL, 0); 

	shmptr->pid1 = pid; 
	shmptr->status = NotReady; 
    sprintf(shmptr->stry, "%d", 5);

	signal(SIGUSR1, handler); 

	while (1) { 
		while (shmptr->status != Ready) 
			continue; 
		sleep(1); 

		printf("User1: "); 
        char buff[100];
        cin.getline(buff, 100);
        int in = atoi(buff);

        x = y + in;
        sprintf(shmptr->strx, "%d", x);

		shmptr->status = FILLED; 

		kill(shmptr->pid2, SIGUSR2); 
	} 

	shmdt((void*)shmptr); 
	shmctl(shmid, IPC_RMID, NULL); 
	return 0; 
} 