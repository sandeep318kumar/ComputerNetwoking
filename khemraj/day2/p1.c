#include<bits/stdc++.h>
#include <fstream> 
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



int main(){    
    int file_desc = open("mytext.txt",O_CREAT | O_RDONLY); 
    dup2(file_desc, 0) ;  
    string str;
    sem_unlink("/parent4");
    sem_unlink("/child4");
    sem_t *parent_semaphore = sem_open("/parent4", O_CREAT | O_RDWR, 0660, 1);
    sem_t *child_semaphore = sem_open("/child4", O_CREAT | O_RDWR, 0660, 0);
    pid_t pid = fork();
    while(cin){
        if(pid>0){
            while(cin){
            sem_wait(parent_semaphore);
            getline(cin,str);
            fflush(stdin);
            cout << getpid() << str << "\n";
            fflush(stdout);
            sem_post(child_semaphore);
            sleep(1);
            }
        }
        else{
            execvp("./p2a",NULL);
            sleep(1);
        }
    }
    sem_close(parent_semaphore);
    sem_close(child_semaphore);
    return 0;
}