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

void *func(void*){
    sleep(2);
    cout<<"In threads\n";
    return NULL;
}
int main()
{
    pthread_t td;
    pthread_create(&td, NULL, func, NULL);
    pthread_join(td, NULL);
    return 0;
}