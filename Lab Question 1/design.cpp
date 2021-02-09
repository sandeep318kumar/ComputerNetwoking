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

void handler(int sig){
    if(sig == SIGUSR1)
    cout<<"Received signal\n";
}
int main()
{
    signal(SIGUSR1, handler);
    int serverid , designid = getpid();

    char* shareid1 = "/tmp/share";
    mkfifo(shareid1, 0666);
    int shfd1 = open(shareid1, O_RDWR);

    char buff[100]= {'\0'};
    sprintf(buff, "%d", designid);
    write(shfd1, buff, 100);
    memset(buff, '\0', sizeof(buff));

    char* shareid2 = "/tmp/share2";
    mkfifo(shareid2, 0666);
    int shfd2 = open(shareid2, O_RDWR);
    read(shfd2, buff, 100);
    serverid = atoi(buff);
    
    cout<<"Server id is: "<<serverid<<" "<<"Process D id is: "<<designid<<endl;

    while(1){
        cout<<"Wanna send signal?\n";
        int ff;
        cin>>ff;
        if(ff == 1){
            kill(serverid, SIGUSR1);
        }
    }
    return 0;
}