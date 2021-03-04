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
    cout<<"hello world\n";
    cout<<"This will print using popen\n";
    char buff[100] = {'\0'};
    cin.getline(buff, 100);
    cout<<buff;
    return 0;
}