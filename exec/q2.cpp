
#include <iostream>
#include <string.h>
#include <stdio.h> 
#include <unistd.h> 
#include <fcntl.h> 
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/wait.h>
#include <unistd.h>
#include <sys/stat.h> 
#include <semaphore.h>
#include <sys/types.h>
#include <fcntl.h>
#include <poll.h>
using namespace std;
#include<stdio.h>
#include<unistd.h>
int main()
{
    printf("Now I am in program 3\n");
    int c = fork();

    if(c > 0){
       cout<<"parent"; 
    }else{
        cout<<"child";
    }
    // printf(p1);
    return 0;
}