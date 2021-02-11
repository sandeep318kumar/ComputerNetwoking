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

bool flag = false;
// false means sending to first grup
// true means sending to second group

int client1, client2;
int r1, r2;

// for clients I am using SIGUSR1
// for readers I am using SIGUSR2

void handler1(int sig){
    if(sig == SIGUSR1){
        cout<<"recieved signal from design\n";
        // sleep(1);
        if(flag == true){
            kill(client1, SIGUSR2);
            // kill(client1, SIGSTOP);
            // kill(client2, SIGCONT);

            // send to reader 1 to stop
            kill(r1, SIGUSR1);
            // kill(r1, SIGSTOP);
            // kill(r2, SIGCONT);

            flag = false;
            cout<<"Switched to first Group\n";
            sleep(1);
        } else {
            kill(client2, SIGUSR2);
            // kill(client1, SIGCONT);
            // kill(client2, SIGSTOP);

            // send to reader to stop
            kill(r2, SIGUSR1);
            // kill(r2, SIGSTOP);
            // kill(r1, SIGCONT);

            flag = true;
            cout<<"Switched to second Group\n";
            sleep(1);
        }
    }
}
void handler2(int sig){
    if(sig == SIGUSR2){
        cout<<"Recieved signal 2 \n";
    }
}

int main()
{
    signal(SIGUSR1, handler1);
    signal(SIGUSR2, handler2);

    int serverid = getpid(), designid;

    // for getting process D id
    char* shareid1 = "/tmp/share";
    mkfifo(shareid1, 0666);
    int shfd1 = open(shareid1, O_RDWR);

    char buff[100]= {'\0'};
    read(shfd1, buff, 100);
    designid = atoi(buff);

    char* shareid2 = "/tmp/share2";
    mkfifo(shareid2, 0666);
    int shfd2 = open(shareid2, O_RDWR);
    memset(buff, '\0', sizeof(buff));
    sprintf(buff, "%d", serverid);
    write(shfd2, buff, 100);    
    
    cout<<"Server id is: "<<serverid<<" "<<"Process D id is: "<<designid<<endl;

    // for getting client1 pid
    char* client1fifo = "/tmp/client1";
    mkfifo(client1fifo, 0666);
    int cfd1 = open(client1fifo, O_RDONLY);
    // char buff[100] = {'\0'};
    read(cfd1, buff, 100);
    client1 = atoi(buff);
    cout<<"Client 1 id is: "<<client1<<endl;

    // for getting client2 pid
    char* client2fifo = "/tmp/client2";
    mkfifo(client2fifo, 0666);
    char buff3[100] = {'\0'};
    int cfd2 = open(client2fifo, O_RDONLY);
    read(cfd2, buff3, 100);
    client2 = atoi(buff3);
    cout<<"Client 2 id is: "<<client2<<endl;


    // for getting reader1 pid
    char* readfifo1 = "/tmp/read1";
    mkfifo(readfifo1, 0666);
    int rfd1 = open(readfifo1, O_RDONLY);
    char rbuff[100] = {'\0'};
    read(rfd1, rbuff, 100);
    r1 = atoi(rbuff);
    cout<<"Reader 1 id is: "<<r1<<endl;

    // for getting reader2 pid
    char* readfifo2 = "/tmp/read2";
    mkfifo(readfifo2, 0666);
    int rfd2 = open(readfifo2, O_RDONLY);
    char rbuff1[100] = {'\0'};
    read(rfd2, rbuff1, 100);
    r2 = atoi(rbuff1);
    cout<<"Reader 2 id is: "<<r2<<endl;

    // now open fifos for reading
    char* getfifo1 = "/tmp/get1";
    mkfifo(getfifo1, 0666);
    int getfd1 = open(getfifo1, O_RDONLY);

    char* getfifo2 = "/tmp/get2";
    mkfifo(getfifo2, 0666);
    int getfd2 = open(getfifo2, O_RDONLY);

    // now open fifos for writing into readers
    char* sendfifo1 = "/tmp/send1";
    mkfifo(sendfifo1, 0666);
    int sendfd1 = open(sendfifo1, O_WRONLY);

    char* sendfifo2 = "/tmp/send2";
    mkfifo(sendfifo2, 0666);
    int sendfd2 = open(sendfifo2, O_WRONLY);

    while(1){
        if(flag == false){
            // from cfd1
            sleep(1);
            char buff1[100] = {'\0'};
            read(getfd1, buff1, 100);
            cout<<"Read this: "<<buff1<<endl;
            // write this to process reader 1
            write(sendfd1, buff1, 100);
        } else {
            // from cfd2
            sleep(1);
            char buff2[100] = {'\0'};
            read(getfd2, buff2, 100);
            cout<<"Read this: "<<buff2<<endl;
            // write this to process reader 2
            write(sendfd2, buff2, 100);
        }
    }

    return 0;
}