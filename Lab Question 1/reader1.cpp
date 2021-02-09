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
using namespace std;

int temp1 = dup(0);
int rfd;
void handler(int sig){
    if(sig == SIGUSR1){
        // change to keyboard
        cout<<"Changed to keyboard\n";
        // dup2(temp1, rfd);
    }
}

int main()
{
    signal(SIGUSR1, handler);
    
    int r = getpid();
    cout<<"Reader 1 id is: "<<r<<endl;
    char* readfifo1 = "/tmp/read1";
    mkfifo(readfifo1, 0666);
    int wfd = open(readfifo1, O_WRONLY);
    char buff[100] = {'\0'};
    sprintf(buff, "%d", r);
    write(wfd, buff, 100);

    cout<<"Wrote this: "<<buff<<endl;

    char* sendfifo = "/tmp/send1";
    mkfifo(sendfifo, 0666);
    rfd = open(sendfifo, O_RDONLY);

    while(1){
        char buff1[100] = {'\0'};
        read(rfd, buff1, 100);
        cout<<"Got this from server: "<<buff1<<endl;
        sleep(1);
    }

    return 0;
}