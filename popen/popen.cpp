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

    // cout<<(int)stdin<<endl;
    cout<<STDIN_FILENO<<endl;
    cout<<STDOUT_FILENO;
    
    FILE *fd = popen("./hell", "w");
    char buff[1024];
    // read(fileno(fd), buff, 1024);
    // cout<<buff<<endl;
    write(fileno(fd), "I am writing", 100);

    return 0;
}