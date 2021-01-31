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

// #include <opencv2/opencv.hpp>
using namespace std;

int makechild(int pip[], int delay, char* msg){
    pipe(pip);
    int c = fork();

    if(c != 0){
        close(pip[1]);
        return c;
    }

    close(pip[0]);
    while(1){
        sleep(delay);
        write(pip[1], msg, strlen(msg));
    }
    exit(0);
    return 0;
}
int main()
{
    int A[2], B[2];
    int pidA = makechild(A, 1, "AA");
    int pidB = makechild(B, 2, "BBB");

    struct pollfd pfds[2];
    pfds[0].fd = A[0];
    pfds[0].events = POLLIN;

    pfds[1].fd = B[0];
    pfds[1].events = POLLIN;

    while(1){
        char buff[1024];
        int k;
        int ret = poll(pfds, 2, -1);
        if(ret < 0){
            perror("Fork() failed\n");
        }

        if(pfds[0].revents & POLLIN){
            k = read(A[0], buff, 1024);
            buff[k] = '\0';
            cout<<"A had: "<<buff<<endl;
        } 
        if(pfds[1].revents & POLLIN){
            k = read(B[0], buff, 1024);
            buff[k] = '\0';
            cout<<"B had: "<<buff<<endl;
        } 
        return 0;
    }
    return 0;
}