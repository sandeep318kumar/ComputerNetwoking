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

bool flag = true;
void handler(int sig){
    if(sig == SIGUSR2){
        cout<<"Need to stop sending now";
        flag = !flag;
    }
}

int main()
{
    signal(SIGUSR2, handler);
    int clientid = getpid();
    cout<<"Client id is: "<<clientid<<endl;

    char* clientfifo = "/tmp/client2";
    mkfifo(clientfifo, 0666);

    int cfd = open(clientfifo, O_WRONLY);
    char buff1[100] ={'\0'};
    sprintf(buff1, "%d", clientid);
    write(cfd, buff1, 100);

    char* getfifo2 = "/tmp/get2";
    mkfifo(getfifo2, 0666);
    int getfd2 = open(getfifo2, O_WRONLY);

    while(1){
        if(flag == true){
            cout<<"What do you wanna write?\n";
            char buff[100] = {'\0'};
            cin.getline(buff, 100);
            write(getfd2, buff, 100);
        }
    }
    return 0;
}