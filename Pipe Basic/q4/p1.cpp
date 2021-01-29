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
    char buff[1024];
    int fd1 = dup(0);

    int c = fork();

    if(c > 0){
        close(B[1]);
        close(A[0]);
            
        int fd2 = dup(0);
        dup2(fd1, 0);
        // while(1){
            cout<<"Type your message to child: ";
            cin.getline(buff, 30);
            dup2(fd2, 0);
            write(A[1], buff, strlen(buff));

            int bytesread = read(B[0], buff, 1024);
            buff[bytesread] = 0;
            cout<<"From child: "<<buff<<endl;
        // }
    } else{
        close(A[1]);
        close(B[0]);

        dup2(A[0], 0);
        // cout<<"child\n";
        execv("./p2a", NULL);
    }
    
    return 0;
}