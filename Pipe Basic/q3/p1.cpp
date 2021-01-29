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
char buff[1024];

int fd1, fd2, fd3, fd4;
char buff[1024];

void* write_parent(void* args){
    close(B[1]);
    cout<<"Parent writing:\n";
    char buff[1024];
    cin.getline(buff, 30);
    write(fd1, buff, strlen(buff));
    return NULL;
}

void* read_parent(void* args){
    close(A[0]);
    char buff[1024];
    int bytesread = read(fd2, buff, 1024);
    buff[bytesread] = 0;
    cout<<"Parent read: "<<buff<<endl;
    return NULL;
}

void* write_child(void* args){
    // close(A[1])
    cout<<"Child writing:\n";
    char buff[1024];
    cin.getline(buff, 30);
    write(fd3, buff, strlen(buff));
    return NULL;
}

void* read_child(void* args){
    char buff[1024];
    int bytesread = read(fd4, buff, 1024);
    buff[bytesread] = 0;
    cout<<"Child read: "<<buff<<endl;
    return NULL;
}

int main()
{
    pipe(A), pipe(B);
    int c = fork();

    if(c > 0){
        close(B[1]);
        close(A[0]);
            
        while(1){
            dup2(A[1], fd1);
            dup2(B[0], fd2);

            pthread_t wp, rp;
            pthread_create(&wp, NULL, write_parent, NULL);
            pthread_create(&rp, NULL, read_parent, NULL);
            pthread_join(wp, NULL);
            pthread_join(rp, NULL);
        }
    } else{
        close(B[0]);
        close(A[1]);

        while(1){
            dup2(B[1], fd3);
            dup2(A[0], fd4);

            pthread_t wc, rc;
            pthread_create(&rc, NULL, read_child, NULL);
            pthread_create(&wc, NULL, write_child, NULL);
            pthread_join(wc, NULL);
            pthread_join(rc, NULL);
        }
    }
    
    return 0;
}