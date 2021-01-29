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

int fd1, fd2,fd3,fd4;
char buff1[100];
void* readParentThread(void* args)
{

    read(fd2,buff1,100);
    cout<<buff1<<":Answer From Child"<<endl;
    return NULL;
}
void* writeParentThread(void* args)
{
    cout << "Write Into A:" << endl;
    char buff[100];
    cin.getline(buff,100);
    write(fd1,buff,100);
    return NULL;
}
void *writeChildThread(void *args)
{
    cout << "Write Into B:" << endl;

    char buff[100];
    cin.getline(buff, 100);
    write(fd4, buff, 100);
    return NULL;
}
void *readChildThread(void *args)
{
    read(fd3, buff1, 100);
    cout << buff1 << ":Answer From Parent" << endl;
    return NULL;
}
int main()
{
    int a[2], b[2];
    char buff[100];

    pipe(a);
    pipe(b);
    int c = fork();
    if(c==0)
    {
        dup2(a[0],fd3);
        dup2(b[1],fd4);
        pthread_t thread_id1, thread_id2;
        pthread_create(&thread_id2, NULL, readChildThread, NULL);
        pthread_create(&thread_id1, NULL, writeChildThread, NULL);
        pthread_join(thread_id1, NULL);
        pthread_join(thread_id2, NULL);
    }
    else
    {
        dup2(a[1],fd1);
        dup2(b[0],fd2);
        pthread_t thread_id1, thread_id2;
        pthread_create(&thread_id1, NULL, writeParentThread, NULL);
        pthread_create(&thread_id2, NULL, readParentThread, NULL);
      
        pthread_join(thread_id1, NULL);
        pthread_join(thread_id2, NULL);
    }
    
    
}