#include<stdio.h>
#include<unistd.h>
#include<pthread.h>
#include<semaphore.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>

sem_t mutex;
int fd;
char buff[128];

void* thread(void* arg) 
{ 
    //wait 
    sem_wait(&mutex); 
    // printf("\nEntered..\n"); 
    // read(fd, buff, 10);
    printf("%s\n", buff);
    //critical section 
    sleep(1); 
    //signal 
    // printf("\nJust Exiting...\n"); 
    sem_post(&mutex); 
}

int main()
{
    fd = open("in.txt", O_RDONLY);
    sem_init(&mutex, 0, 1);
    pthread_t t1, t2; 
    while(read(fd, buff, 10) > 0){
        printf("Read this: %s\n", buff);
        pthread_create(&t1, NULL, thread, NULL); 
        // sleep(2); 
        read(fd, buff, 10);
        printf("Read this: %s\n", buff);
        // if(read(fd, buff, 10) > 0)
            pthread_create(&t2, NULL, thread, NULL);
        // else 
            // break;
        pthread_join(t2, NULL); 
        pthread_join(t1, NULL);
    }
    
    return 0;
}