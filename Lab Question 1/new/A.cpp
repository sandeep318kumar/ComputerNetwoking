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

int flag = 0;
void h1(int sig)
{
    flag = 0;
    cout<<"STOP\n";
}

void h2(int sig){
    flag = 1;
    cout<<"Continue\n";
}
void die(char *s)
{
  perror(s);
  exit(1);
}
int main()
{
    cout<<"I am A\n";
    signal(SIGUSR1, h1);
    signal(SIGUSR2, h2);

    cout<<"Enter group id: ";
    pid_t x;
    cin>>x;
    int t = setpgid(getpid(), x);
    if(t < 0){
        cout<<t<<endl;
       die("setpgid");
    }
    cout<<t<<endl;
    cout<<"This process id: "<<getpid();
    cout<<"\n, Group id: "<<getpgid(getpid());
    while(1){
        if(flag == 1){
            char buff[100];
            read(0, buff, 100);
            cout<<"Read this: "<<buff<<endl;
        } 
        // else{
        //     cout<<"Taking input from keyboard\n";
        // }
    }
    return 0;
}