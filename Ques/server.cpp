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
#include <sys/shm.h>
using namespace std;

struct memory {    
    int pid, status, cnt; 
    char buff1[30];
    char buff2[100];        
};
struct memory* shmptr;

bool flag = false;
void handler(int sig){
    cout<<"Recieved this signal: "<<sig<<endl;
    flag = true;
}
int main()
{
    signal(SIGUSR1, handler);

    key_t key = ftok("shmfile", 65);

    int shmid = shmget(key, sizeof(struct memory), IPC_CREAT | 0666);
    shmptr = (struct memory*)shmat(shmid, NULL, 0);

    shmptr->pid = getpid();
    char buff[30] = {'\0'};
    strcpy(shmptr->buff1, buff);
    strcpy(shmptr->buff1, "hello\n");

    char buff1[100] = {'\0'};
    strcpy(shmptr->buff2, buff1);
    strcpy(shmptr->buff2, "there\n");

    struct iovec iov[2];
    iov[0].iov_base = shmptr->buff1;
    iov[0].iov_len = strlen(shmptr->buff1);
    iov[1].iov_base = shmptr->buff2;
    iov[1].iov_len = strlen(shmptr->buff2);
    int iovcnt = sizeof(iov) / sizeof(struct iovec);


    while(1){
        if(flag){
            cout<<"Reading now\n";
            cout<<shmptr->buff1<<endl;
            cout<<shmptr->buff2<<endl;
            break;
        }
    }
    shmdt((void*)shmptr);
    shmctl(shmid, IPC_RMID, NULL);
    return 0;
}