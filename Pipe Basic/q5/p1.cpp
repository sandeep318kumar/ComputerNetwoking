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

int A[2], B[2];

void* write_parent(void* argv){

    while(1){
        // cout<<"Parent writing: \n";
        char buff[1024];
        cin.getline(buff, 30);
        cout<<"Parent writing: "<<buff<<endl;
        
        write(A[1], buff, 1024);
        sleep(1);
        fflush(stdin);
    }
    return NULL;
}

void* read_parent(void* argv){

    while(1){
        char buff[1024];
        read(B[0], buff, 1024);
        cout<<"Parent read: "<<buff<<endl;
    }
    return NULL;
}

int main()
{
    pipe(A), pipe(B);
    char buff1[1024], buff2[1024];
    int stdi = dup(STDIN_FILENO);
    int stdo = dup(STDOUT_FILENO);
    dup2(A[0], 0);
    dup2(B[1], 1);

    int c = fork();

    if(c > 0){
        close(B[1]);
        close(A[0]);
        
        dup2(stdi, STDIN_FILENO);
        dup2(stdo, STDOUT_FILENO);

        pthread_t wp, rp;
        pthread_create(&wp, NULL, write_parent, NULL);
        pthread_create(&rp, NULL, read_parent, NULL);
        pthread_join(wp, NULL);
        pthread_join(rp, NULL);
    } else{
        execv("./p2a", NULL);
    }
    
    return 0;
}