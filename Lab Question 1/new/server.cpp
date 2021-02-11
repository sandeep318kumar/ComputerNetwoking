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
#include <sys/shm.h>
using namespace std;

struct memory {    
    int pid, status, cnt;              
};
struct memory* shmptr;

int send = 0;
int A[2], B[2];
char buff[100];
char * myfifo = "/tmp/hello"; 

void writeg1(){
    // killpg(321, SIGUSR2);
   
    write(A[1], buff, 100);
    write(B[1], buff, 100);
    cout<<"In buffer: "<<buff<<endl;
    // killpg(321, SIGUSR1);
}

void writeg2(){

    FILE* fd1 = popen("./Ax", "w");
    // FILE* fd2 = popen("./Bx", "w");

    // killpg(123, SIGUSR2);

    write(fileno(fd1), buff, 100);
    cout<<"In buffer: "<<buff<<endl;
    // write(fileno(fd2), buff, 100);
    // killpg(123, SIGUSR1);
}

void readData(){
    mkfifo(myfifo, 0666);
    int fd = open(myfifo, O_RDONLY);    
    read(fd, buff, 100);
    cout<<"Server Read this:  "<<buff<<endl;
    close(fd);
}

// for handling signals sent to S
void handler1(int si){
    cout<<"Recieved SIGUSR1\n";
    sleep(1);
}
void handler2(int si){
    cout<<"Recieved SIGUSR2\n";
    sleep(1);
}

// for handling signals in child processes
void h1(int sig){
    send = 0;
    cout<<"Stopped\n";
    sleep(1);
}

void h2(int sig){
    send = 1;
    cout<<"Continue\n";
    sleep(1);
}

int main()
{
    pipe(A), pipe(B);

    int c = fork();
    if(c > 0){

        int c2 = fork();
        if(c2 > 0){
            // in server
            key_t key = ftok("shmfile", 65);
            int shmid = shmget(key, sizeof(struct memory), IPC_CREAT | 0666);
            shmptr = (struct memory*)shmat(shmid, NULL, 0);

            shmptr->pid = getpid();
            shmptr->cnt = 0;
            shmptr->status = 0;
            cout<<"Server id is: "<<getpid()<<endl;

            signal(SIGUSR1, handler1);
            signal(SIGUSR2, handler2);

            while(1){
                if(shmptr->status == 1){
                    // G1
                    killpg(321, SIGUSR1);
                    while(shmptr->status == 1){
                        // write to G2
                        readData();
                        writeg2();
                    }
                    killpg(321, SIGUSR2);
                }
                if(shmptr->status == 2){
                    // G2
                    killpg(123, SIGUSR1);
                    while(shmptr->status == 2){
                        // write to G2
                        readData();
                        writeg2();
                    }
                    killpg(123, SIGUSR2);
                }
                
            }
            
            shmdt((void*)shmptr);
            shmctl(shmid, IPC_RMID, NULL);
        } else{
            // i am s'
            setpgid(getpid(), 123);

            signal(SIGUSR1, h1);
            signal(SIGUSR2, h2);
            cout<<"I am S': "<<getpid()<<", Group id: "<<getpgid(123);
            while(1){
                if(send == 1){
                    while(send == 1){
                        char buff1[100] = {'\0'};
                        read(B[0], buff1, 100);
                        cout<<"I am S'', Read this: "<<buff1<<endl;
                        sleep(1);
                    }
                } 
                // else if(send == 0){
                //     cout<<"Switched to keyboard\n";
                //     sleep(1);
                // }
            }
        }
    } else{
        // i am s''
        setpgid(getpid(), 123);

        signal(SIGUSR1, h1);
        signal(SIGUSR2, h2);

        cout<<"I am S'' "<<getpid()<<", Group id: "<<getpgid(123);
        while(1){
            if(send == 1){
                while(send == 1){
                    char buff1[100] = {'\0'};
                    read(B[0], buff1, 100);
                    cout<<"I am S'', Read this: "<<buff1<<endl;
                    sleep(1);
                }
            } 
            //else if(send == 0){
            //     cout<<"Switched to keyboard\n";
            //     sleep(1);
            // }
        }
    }

    return 0;
}