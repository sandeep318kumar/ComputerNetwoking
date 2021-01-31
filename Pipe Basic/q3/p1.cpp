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

void* write_parent(void* argv){
    // close(B[1]);
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
    // close(A[0]);
    while(1){
        char buff[1024];
        read(B[0], buff, 1024);
        // buff[bytesread] = 0;
        cout<<"Parent read: "<<buff<<endl;
    }
    return NULL;
}

void* write_child(void* argv){
    // close(A[1])
    while(1){
        // cout<<"Child writing:\n";
        char buff[1024];
        cin.getline(buff, 1024);
        cout<<"Child writing: "<<buff<<endl;
        write(B[1], buff, strlen(buff));
        fflush(stdin);
    }
    return NULL;
}

void* read_child(void* argv){
    while(1){
        char buff[1024];
        int bytesread = read(A[0], buff, 1024);
        buff[bytesread] = 0;
        cout<<"Child read: "<<buff<<endl;
    }
    return NULL;
}

int main()
{
    pipe(A), pipe(B);
    int c = fork();

    if(c > 0){
        close(B[1]);
        close(A[0]);
   
        pthread_t wp, rp;
        pthread_create(&wp, NULL, write_parent, NULL);
        pthread_create(&rp, NULL, read_parent, NULL);
        pthread_join(wp, NULL);
        pthread_join(rp, NULL);
    } else{
        close(B[0]);
        close(A[1]);

        pthread_t wc, rc;
        pthread_create(&rc, NULL, read_child, NULL);
        pthread_create(&wc, NULL, write_child, NULL);
        pthread_join(wc, NULL);
        pthread_join(rc, NULL);
    }
    
    return 0;
}