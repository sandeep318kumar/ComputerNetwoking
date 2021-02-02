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

int x = 5, y;
int sfd, xfd, yfd;

void handler(int sig){
    cout<<"Got signal from P2\n";
    char stry[20] = {'\0'};
    read(yfd, stry, 20);
    y = atoi(stry);
    cout<<"Got this value of y = "<<y<<endl;
}
int main() 
{
    signal(SIGUSR2, handler);
    
    pid_t p1 = getpid(), p2;
    char* myfifo = "/tmp/share";
    mkfifo(myfifo, 0666);
    sfd = open(myfifo, O_RDWR);

    char* xfifo = "/tmp/x";
    mkfifo(xfifo, 0666);
    xfd = open(xfifo, O_RDWR);

    char* yfifo = "/tmp/y";
    mkfifo(yfifo, 0666);
    yfd = open(yfifo, O_RDWR);

    char sp1[6] = {'\0'};
    sprintf(sp1, "%d", p1);
        
    write(sfd, sp1, 6);
    cout<<"your process id is: "<<sp1<<endl;

    char buff[6] = {'\0'};
    read(sfd, buff, 6);
    p2 = atoi(buff);
    cout<<"other Process id is: "<<p2<<endl;

    char strx[20] = {'\0'};
    sprintf(strx, "%d", x);
    write(xfd, strx, 20);
    // cout<<"P1 wrote x = "<<x<<endl;
    while(1){
        kill(p2, SIGUSR1);
        
        char buff1[100];
        cin.getline(buff1, 100);
        int in = atoi(buff1);

        x = y + in;
        char strx[20] = {'\0'};
        sprintf(strx, "%d", x);
        write(xfd, strx, 20);
        // cout<<"P1 wrote x = "<<x<<endl;
    }
    
}