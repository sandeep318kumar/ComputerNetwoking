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

int main()
{
    int A[2], B[2];
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

        while(1){
            // cout<<"Type your message to child: ";
            cin.getline(buff1, 1024);
            // dup2(fd2, 0);
            write(A[1], buff1, 1024);
            cout<<"Parent wrote: "<<buff1<<endl;

            read(B[0], buff2, 1024);
            cout<<"Parent read: "<<buff2<<endl;
            // cout<<"From child: "<<buff2<<endl;
        }
        close(A[1]);
        close(B[0]);
    } else{
        
        execv("./p2a", NULL);
    }
    
    return 0;
}