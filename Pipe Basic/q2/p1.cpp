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
    // int c = fork();

    // for(int i=0;i<3;i++)
    // if(c > 0){
    //     cout<<"Parent\n";
    //     cout<<"Parent 1\n";
    //     cout<<"Parent 2\n";


    // } else {
    //     cout<<"Child\n";
    //     cout<<"Child 1\n";
    //     cout<<"Child 2\n";
    // }



// 84455 12165

    int A[2], B[2];
    pipe(A), pipe(B);
    char buff[1024];

    int c = fork();

    // char* m1 = "message from parent";
    if(c > 0){
        close(B[1]);
        close(A[0]);
            
        while(1){
            cout<<"Type your message to child: ";
            cin.getline(buff, 30);
            write(A[1], buff, strlen(buff));

            int bytesread = read(B[0], buff, 1024);
            buff[bytesread] = 0;
            cout<<"From child: "<<buff<<endl;
        }
    } else{
        close(B[0]);
        close(A[1]);

        while(1){
            int bytesread = read(A[0], buff, 1024);
            buff[bytesread] = 0;
            
            cout<<"From Parent: "<<buff<<endl;

            cout<<"Type your message to Parent: ";
            cin.getline(buff, 30);
            write(B[1], buff, strlen(buff));
        }
    }
    
    return 0;
}