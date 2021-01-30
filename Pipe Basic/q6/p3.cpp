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

    // cout<<"This is p3\n";
    FILE* fd1 = popen("./p4a", "r");

    char buff[1024];
    read(fileno(fd1), buff, 1024);
    cout<<"From p4: "<<buff<<endl;
    pclose(fd1);
}