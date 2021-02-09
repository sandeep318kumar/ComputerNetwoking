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
int x = 5, y;
void handler(int signum) 
{ 
	if (signum == SIGUSR2) { 
		printf("Received From User1: "); 
		cout<<shmptr->strx<<endl;
        x = atoi(shmptr->strx);
	} 
} 

int main() 
{ 
	int pid = getpid(); 
	int shmid; 
	int key = 12345; 
	shmid = shmget(key, sizeof(struct memory), IPC_CREAT | 0666); 
	shmptr = (struct memory*)shmat(shmid, NULL, 0); 

	shmptr->pid2 = pid; 

	shmptr->status = NotReady; 
    sprintf(shmptr->strx, "%d", 5);

	signal(SIGUSR2, handler); 

	while (1) { 
		sleep(1); 

		printf("User2: "); 
		char buff[100];
        cin.getline(buff, 100);
        int in = atoi(buff);
		
        y = in + x;

        sprintf(shmptr->stry, "%d", y);
        
        shmptr->status = Ready; 

		kill(shmptr->pid1, SIGUSR1); 
		while (shmptr->status == Ready) 
			continue; 
	} 

	shmdt((void*)shmptr); 
	return 0; 
} 