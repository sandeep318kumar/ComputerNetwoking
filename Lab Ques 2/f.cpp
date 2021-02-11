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

void handler(int sig){
    cout<<"Recieved this signal: "<<sig<<endl;
}

int main()
{
    cout<<"Hi, my pid is: "<<getpid()<<endl;
    signal(SIGUSR1, handler);

    // for semaphores
    sem_unlink("/s");
    sem_unlink("/s1");
    sem_unlink("/s2");
    sem_unlink("/s3");
    sem_t *s = sem_open("/s",   O_CREAT | O_RDWR, 0660, 0);
    sem_t *s1 = sem_open("/s1", O_CREAT | O_RDWR, 0660, 0);
    sem_t *s2 = sem_open("/s2", O_CREAT | O_RDWR, 0660, 0);
    sem_t *s3 = sem_open("/s3", O_CREAT | O_RDWR, 0660, 0);
    cout<<"I am waiting\n";
    sem_wait(s);
    sem_wait(s);
    sem_wait(s);
    cout<<"I am running\n";
    sem_post(s1);
    sem_post(s2);
    sem_post(s3);

    return 0;
}