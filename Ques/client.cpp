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

void handler(int sig){
    cout<<"Recieved this signal: "<<sig<<endl;
}

int main()
{
	signal(SIGUSR1, handler);
    cout<<"Hi, my pid is: "<<getpid()<<endl;

    key_t key = ftok("shmfile", 65);

    int shmid = shmget(key, sizeof(struct memory), IPC_CREAT | 0666);
    shmptr = (struct memory*)shmat(shmid, NULL, 0);

    int pp = shmptr->pid;

    int fd = open("out.txt", O_RDWR);
    
    struct iovec iov[2];
    iov[0].iov_base = shmptr->buff1;
    iov[0].iov_len = strlen(shmptr->buff1);
    iov[1].iov_base = shmptr->buff2;
    iov[1].iov_len = strlen(shmptr->buff2);
    int iovcnt = sizeof(iov) / sizeof(struct iovec);
    writev(fd, iov, iovcnt);

    char buff[1024] = {'\0'};
    int fd1 = open("out.txt", O_RDONLY);
    read(fd1, buff, 1024);
    cout<<buff<<endl;

    // writing to share memory;
    char buff2[30] = {'\0'};
    strcpy(shmptr->buff1, buff2);
    char buff1[100] = {'\0'};
    strcpy(shmptr->buff2, buff1);

    // struct iovec myiov[2];
    // myiov[0].iov_base = shmptr->buff1;
    // myiov[0].iov_len = strlen(shmptr->buff1);
    // myiov[1].iov_base = shmptr->buff2;
    // myiov[1].iov_len = strlen(shmptr->buff2);
    // int iovcnt1 = sizeof(myiov) / sizeof(struct iovec);

    int fd2 = open("in.txt", O_RDONLY);
    // read(fd2, buff1, 100);
    // cout<<"Read this in file desc: "<<buff1<<endl;
    readv(fd2, iov, iovcnt);
    kill(pp, SIGUSR1);
    shmdt((void*)shmptr);
    shmctl(shmid, IPC_RMID, NULL);
    return 0;
}