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
void handler1(int sig){
    cout<<"Received this signal in parent: "<<sig<<endl;
}
void handler2(int sig){
    cout<<"Received this signal in child: "<<sig<<endl;
}
int main() 
{ 
    pid_t pid, pp = getpid(); 
    int status; 
    signal(SIGUSR1, handler1); 
    pid = fork();
    if(pid > 0) 
    { 
        cout<<"In Parent: "<<pid<<endl;
        kill(pid, SIGUSR1);
        while(1);
    } 
    else{
        signal(SIGUSR1, handler2); 
        cout<<"in child\n";
       
        kill(getppid(), SIGUSR1); 
        while(1) ;  
    }
}