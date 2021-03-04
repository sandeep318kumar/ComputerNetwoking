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
	cout<<"Hi, my pid is: "<<getpid()<<endl;
	signal(SIGUSR1, handler);

	// for message queue
	key_t key;
	key = 1234;

    int pid = getpid();
	int msgid;
	msgid = msgget(key, 0666 | IPC_CREAT);

	if(msgid == -1){
		die("msgget");
	}
	cout<<"Message id is: "<<msgid<<endl;
    
    sem_t *s43 = sem_open("/s43", 0);
    sem_t *s23 = sem_open("/s23", 0);

    message.msg_type = pid;
    if(msgsnd(msgid, &message, sizeof(message), 0) == -1){
        die("msgsnd");
    }
    sem_post(s23);
    sleep(1);
    sem_wait(s43);
    cout<<"getting the message\n";
    if(msgrcv(msgid, &message, sizeof(message), 0, 0) == -1){
        die("msgrcv");
    }

    int p4 = message.msg_type;
    kill(p4, SIGUSR1);
    cout<<"Got pid of P4: "<<p4<<endl;

    sleep(10);

    while(1){

    }

    return 0;
}