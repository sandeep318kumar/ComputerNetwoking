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
using namespace std;

int x, y = 10;
int sfd, xfd, yfd;

void handler(int sig){
    cout<<"Got signal from P1\n";
    char strx[20] = {'\0'};
    read(xfd, strx, 20);
    x = atoi(strx);
    cout<<"Got x value is: "<<x<<endl;
}

int main() 
{ 
    signal(SIGUSR1, handler);

    pid_t p1, p2 = getpid();
    char* myfifo = "/tmp/share";
    mkfifo(myfifo, 0666);
    sfd = open(myfifo, O_RDWR);

    char* xfifo = "/tmp/x";
    mkfifo(xfifo, 0666);
    xfd = open(xfifo, O_RDWR);

    char* yfifo = "/tmp/y";
    mkfifo(yfifo, 0666);
    yfd = open(yfifo, O_RDWR);

    char buff[6];
    read(sfd, buff, 6);
    p1 = atoi(buff);
    cout<<"other Process id is: "<<p1<<endl;
    
    char sp2[6] = {'\0'};
    sprintf(sp2, "%d", p2);
    
    write(sfd, sp2, 6);
    cout<<"your process id is: "<<sp2<<endl;

    char stry[20] = {'\0'};
    sprintf(stry, "%d", y);
    write(yfd, stry, 20);
    // cout<<"P2 wrote y = "<<y<<endl;

    while(1){
        kill(p1, SIGUSR2);
        
        char buff1[100];
        cin.getline(buff1, 100);
        int in = atoi(buff1);

        y = x + in;
        char stry[20] = {'\0'};
        sprintf(stry, "%d", y);
        write(yfd, stry, 20);
        // cout<<"P2 wrote y = "<<y<<endl;
    }
}