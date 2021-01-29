#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include<pthread.h>
#include<semaphore.h>


int main()
{
    int c = fork();

    for(int i=0;i<5;i++){
        if(c > 0){
            printf("Parent: %d\n", i);
        } else{
            printf("Child: %d\n", i);
        }
    }

    return 0;
}