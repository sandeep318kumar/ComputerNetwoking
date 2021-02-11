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
#include <sys/shm.h>
#include <sys/resource.h>
using namespace std;

struct memory {    
    int pid, status, cnt;              
};
struct memory* shmptr;

int main()
{
    key_t key = ftok("shmfile",65);

    int x;
    int shmid = shmget(key, sizeof(struct memory), IPC_CREAT | 0666);
    shmptr = (struct memory*)shmat(shmid, NULL, 0);

    int serverpid = shmptr->pid;
    cout<<"Server id is: "<<serverpid<<endl;
    
    while(1)
    {
        cout<<"Enter 1 to send to G1\n and 2 to send to G2\n";
        int x;
        cin>>x;
        if(x == 1){
            shmptr->status = 1;
            cout<<"To Group 1\n";
            kill(serverpid, SIGUSR1);
            shmptr->cnt++;
        } else if(x == 2) {
            shmptr->status = 2;
            cout<<"To Group 2\n";
            kill(serverpid, SIGUSR2);
            shmptr->cnt++;
        } else{
            cout<<"oops!, choose carefully\n";
        }
    }

    shmdt((void*)shmptr);
    shmctl(shmid, IPC_RMID, NULL);
    return 0;
}