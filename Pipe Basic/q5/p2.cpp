#include<iostream>
#include<string.h>
#include<stdio.h> 
#include<unistd.h> 
#include<fcntl.h> 
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/wait.h>
#include <unistd.h>
#include <semaphore.h>
#include <sys/types.h>
#include <fcntl.h>
using namespace std;

int rfd, wfd;

void* write_child(void* argv){
    
    while(1){
        // cout<<"Child writing:\n";
        char buff[1024];
        cin.getline(buff, 1024);
        cout<<"Child writing: "<<buff<<endl;
        write(wfd, buff, strlen(buff));
        fflush(stdin);
    }
    return NULL;
}

void* read_child(void* argv){
    while(1){
        char buff[1024];
        read(rfd, buff, 1024);
        cout<<"Child read: "<<buff<<endl;
    }
    return NULL;
}
int main()
{
    
    char buff1[1024], buff2[1024];
    // cout<<STDIN_FILENO<<endl;
    // cout<<STDOUT_FILENO<<endl;
    
    rfd = dup(STDIN_FILENO);
    wfd = dup(STDOUT_FILENO);

    // cout<<STDIN_FILENO<<endl;
    // cout<<STDOUT_FILENO<<endl;
    
    dup2(7, STDIN_FILENO);
    dup2(8, STDOUT_FILENO);

    pthread_t wc, rc;
    pthread_create(&rc, NULL, read_child, NULL);
    pthread_create(&wc, NULL, write_child, NULL);
    pthread_join(wc, NULL);
    pthread_join(rc, NULL);

    return 0;
}