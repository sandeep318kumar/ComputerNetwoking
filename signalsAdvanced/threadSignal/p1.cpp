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

pthread_t t1, t2;
void handle1(int sig){
    cout<<"I am handler 1\n";
}
void handle2(int sig){
    cout<<"I am handler 2\n";
}

void* fort1(void* argv){
    int p = 2;
    while(p--){
        cout<<"Thread 1 is running: "<<t1<<endl;
        sleep(1);
        pthread_kill(t2, SIGUSR2);
    }
}

void* fort2(void* argv){
    int p = 2;
    while(p--){
        cout<<"Thread 2 is running: "<<t2<<endl;
        sleep(1);
        pthread_kill(t1, SIGUSR1);
    }
}
int main() 
{ 
    signal(SIGUSR2, handle1);
    signal(SIGUSR1, handle2);

    pthread_create(&t1, NULL, fort1, NULL);
    pthread_create(&t2, NULL, fort2, NULL);

    cout<<"Thread 1 id is: "<<t1<<"\nThread 2 id is: "<<t2<<endl;
    // pthread_kill(t1, SIGUSR2);
    // pthread_kill(t2, SIGUSR1);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    return 0;
}