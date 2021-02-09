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
using namespace std;
#include<wait.h> 
#include<signal.h> 
pid_t pid; 
int counter = 0; 
void handler1(int sig) 
{ 
    counter++; 
    printf("counter = %d\n", counter); 
    /* Flushes the printed string to stdout */
    // fflush(stdout); 
    cout<<"pid is: "<<getpid()<<endl;
    kill(pid, SIGUSR1); 
} 
void handler2(int sig) 
{ 
    counter += 3; 
    printf("counter = %d\n", counter); 
    exit(0); 
} 
  
int main() 
{ 
    pid_t p; 
    int status; 
    signal(SIGUSR1, handler1); 
    if ((pid = fork()) == 0) 
    { 
        cout<<"in child\n";
        cout<<"Child id is: "<<getpid()<<" Parent pid is: "<<getppid()<<endl;
        signal(SIGUSR1, handler2); 
        kill(getppid(), SIGUSR1); 
        while(1) ; 
    } 
    if ((p = wait(&status)) > 0) 
    { 
        cout<<"In Parent\n";
        counter += 4; 
        printf("counter = %d\n", counter); 
    } 
}