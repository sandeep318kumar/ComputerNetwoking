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


int main(int argc, char* argv[])
{
    char buff1[1024], buff2[1024];
    int rd, wd;
    rd = dup(STDIN_FILENO);
    wd = dup(STDOUT_FILENO);

    while(1){

        read(rd, buff1, 1024);
        // cout<<"From Parent: "<<buff1<<endl;
        cout<<"Child read: "<<buff1<<endl;
        dup2(7, STDIN_FILENO);
        dup2(8, STDOUT_FILENO);

        memset(buff2,  0, sizeof(buff2));
        cin.getline(buff2, 1024);
        // cout<<"Type your message to Parent: "<<buff2;
        
        write(wd, buff2, 1024);
        cout<<"Child write: "<<buff2<<endl;
    }
    close(rd);
    close(wd);
    return 0;
}