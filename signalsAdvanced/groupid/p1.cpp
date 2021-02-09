#include<bits/stdc++.h>
#include<stdio.h>
#include<fcntl.h>
#include<unistd.h>
#include<sys/wait.h>
#include<semaphore.h>
#include <sys/ipc.h> 
#include <sys/mman.h>
#include <sys/types.h>
#include<sys/stat.h>
#include <stdlib.h>
#include<pthread.h>
#include<sys/shm.h>
#include <dirent.h>
#include <sys/resource.h>
#include <signal.h>
using namespace std; 

void handle(int sig){
    cout<<"I am P1: I recieved SIGUSR1 signal\n";
    exit(0);
    return;
}

void handle5(int sig){
    cout<<"I am P5: I recieved SIGUSR1 signal\n";
    exit(0);
    return;
}

void handle2(int sig){
    cout<<"I am P2: I recieved SIGUSR1 signal\n";
    exit(0);
    return;
}

void handle3(int sig){
    cout<<"I am P3: I recieved SIGUSR1 signal\n";
    exit(0);
    return;
}

void handle4(int sig){
    cout<<"I am P4: I recieved SIGUSR1 signal\n";
    exit(0);
    return;
}

int main()
{
    int c1;
    int pid = getpid();
    cout<<"P1: "<<pid<<"\n";
    c1 = fork();
    if(c1>0){
        int c2 = fork();
        if(c2>0){
            int c3 = fork();
            if(c3>0){
                int c4 = fork();
                if(c4>0){
                    int c = fork();
                    if(c>0){
                        signal(SIGUSR1,handle);
                        sleep(2);
                    }
                    else{
                        sleep(1);
                        killpg(pid,SIGUSR1);
                    }
                }
                else{
                    //p5
                    //sleep(1);
                    signal(SIGUSR1,handle5);
                    setgid(getppid());
                    cout<<"P5: ";
                    cout<<getpgrp()<<"\n";
                    while(1){

                    }
                }
            }
            else{
                //p4
                //sleep(1);
                signal(SIGUSR1,handle4);
                setpgid(0,getppid());
                cout<<"P4: ";
                cout<<getpgrp()<<"\n";
                while(1){

                }
            }
        }
        else{
            //p3
            //sleep(1);
            signal(SIGUSR1,handle3);
            setpgid(0,getppid());
            cout<<"P3: ";
            cout<<getpgrp()<<"\n";
            while(1){

            }
        }
    }
    else{
        //p2
        //sleep(1);
        signal(SIGUSR1,handle2);
        setpgid(0,getppid());
        cout<<"P2: ";
        cout<<getpgrp()<<"\n";
        while(1){

        }
    }
    return 0;
}