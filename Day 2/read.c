#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include<pthread.h>
#include<semaphore.h>

int main(int argc, char *argv[])
{
    int fd;
    char buff[128];
    fd = open("in.txt", O_RDONLY);
    int c = fork();
    sem_t parent, child;
    sem_init(&parent, 1, 1);
    sem_init(&child, 1, 0);

// read 10 in parent and 10 char in child
   while( read(fd, buff, 11) > 0) {
    //    read(fd, buff, 10);
       if(c > 0){
            printf("Parent printing\n");
            sem_wait(&parent);
            printf("Parent: %s\n", buff);
            sem_post(&child);
        } else
        {
            printf("child printing\n");
            sem_wait(&child);
            printf("child: %s\n", buff);  
            sem_post(&parent); 
        }
   }
   
  return 0;
}   