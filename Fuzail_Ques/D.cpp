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
#include <sys/shm.h>
#include <semaphore.h>
#include <sys/types.h>
#include <fcntl.h>
#include <poll.h>
#include<signal.h>

struct memory {
    int pid;
    int cnt;
};
struct memory* X;

int main()
{
    int key2 = 333;
    int shmid2 = shmget(key2, sizeof(struct memory), IPC_CREAT | 0666);
    X = (struct memory*)shmat(shmid2, NULL, 0);
    
    while(1)
    {
        sleep(3);
        kill(X->pid,SIGUSR1);
        X->cnt++;
    }
    
    
        
}





