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
using namespace std;

int pfd;
int mfd;
char spid[6] = {'\0'};
char connect[100] = {'\0'};

void* read_client(void* argv){
    while(1){
        char buff[1024] = {'\0'};
        read(pfd, buff, 1024);
        cout<<buff<<endl;
    }
}

void* write_client(void* argv){
    while(1){
        char buff[1024] = {'\0'};
        // strcat(buff, "@");
        strcat(buff, spid);
        strcat(buff, "#");
        char buff1[1024];
        cin.getline(buff1, 1024);
        strcat(buff, buff1);
        write(mfd, buff, 1024);
    }
}
int main()
{
    int res;
    cout<<"Do you wanna join NITW??\n";
    cin>>res;
    if(res == 1){
        cout<<"your pid is: "<<getpid()<<endl;
        int pid = getpid();
        
        sprintf(spid, "%d", pid);
        // cout<<spid<<endl;
        strcat(connect, "#");
        strcat(connect, spid);
        

        char * myfifo = "/tmp/NITW"; 
        mkfifo(myfifo, 0666); 
        mfd = open(myfifo, O_WRONLY);
        
        write(mfd, connect, 100);
        // cout<<"Let's go to for creating our pipe: "<<spid<<endl;
        
        char per[100] = {'\0'};
        char* personal = "/tmp/";
        strcpy(per, personal);
        strcat(per, spid);
        cout<<"This is your personal fifo: "<<per<<endl;

        // write(mfd, per, 100);
        // write(mfd, "I am Here", 100);

        int cr = mkfifo(per, 0666);
        if(cr < 0){
            printf("Error: %s\n", stderr);
        }
        pfd = open(per, O_RDWR);


        pthread_t wr, rd;
        pthread_create(&rd, NULL, read_client, NULL);
        pthread_create(&wr, NULL, write_client, NULL);

        pthread_join(wr, NULL);
        pthread_join(rd, NULL);

    }
    return 0;
}