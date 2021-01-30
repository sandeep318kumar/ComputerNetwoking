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

    // cout<<"This is p2\n";
    FILE* fd1 = popen("./p3a", "r");

    char buff[1024];
    read(fileno(fd1), buff, 1024);
    cout<<"From p3: "<<buff<<endl;
    pclose(fd1);
}