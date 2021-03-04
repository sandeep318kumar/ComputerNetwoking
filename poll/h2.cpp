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

struct message_buffer{
    long msg_type;
    char msgtext[1024];
} message;

struct memory {    
    int pid, status, cnt; 
    char buff2[100];
    char buff1[100];         
};
struct memory* shmptr;

void handler(int sig){
    cout<<"Recieved this signal: "<<sig<<endl;
}

int main()
{
    // cout<<"Hi, my pid is: "<<getpid()<<endl;
    // signal(SIGUSR1, handler);

    // // for message queue
    // key_t key;
    // key = 1234;

    // int msgid;
    // msgid = msgget(key, 0666 | IPC_CREAT);

    // if(msgid == -1){
    //     die("msgget");
    // }
    // cout<<"Message id is: "<<msgid<<endl;
    
    // // for shared memory
    // key_t key = ftok("shmfile",65);
    // int shmid = shmget(key, sizeof(struct memory), IPC_CREAT | 0666);
    // shmptr = (struct memory*)shmat(shmid, NULL, 0);

    // shmptr->pid = getpid();
    // strcpy(shmptr->buff1, "hello");
    // strcpy(shmptr->buff2, "there");




    // msgctl(msgid, IPC_RMID, NULL);
    // shmdt((void*)shmptr);
    // shmctl(shmid, IPC_RMID, NULL);
    while(1){
        char buff[100] = {'\0'};
        cin.getline(buff, 100);
        cout<<"entered: "<<buff<<endl;
    }
    return 0;
}