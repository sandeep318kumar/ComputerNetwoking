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

    FILE *fd = popen("ls -l", "r");
    char buff[1024];
    fread(buff, sizeof(char), 1024, fd);
    cout<<buff<<endl;

    return 0;
}