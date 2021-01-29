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
    int pp[2];
    pipe(pp);
    char buff[128];
    int c = fork();

    char* m1 = "message from parent";
    if(c > 0){
        cout<<"Parent process\n";
        write(pp[1], m1, 60);
        write(pp[1], "another message from parent", 60);
        // wait(NULL);
        exit(1);
    } else{
        cout<<"child process\n";
        while(read(pp[0], buff, 60) > 0)
            cout<<buff<<endl;
        exit(2);
        // cout<<buff<<endl;
    }


    return 0;
}