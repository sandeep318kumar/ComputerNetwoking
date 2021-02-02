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


int main()
{

    int fd = 0;
    char buff[100];
    int ret, pret;

    struct pollfd fds[1];
    int timeout;

    while(1){
        fds[0].fd = fd;
        fds[0].events = 0;
        fds[0].events |= POLLIN;
        timeout = 5000;

        pret = poll(fds, 1, timeout);
        if(pret == 0){
            cout<<ret<<endl;
            cout<<timeout<<endl;

        }
        else{
            memset(buff, '\0', 100);
            ret = read(fd, buff, 100);
            cout<<ret<<endl;
            if(ret != -1){
                cout<<"Buffer is: "<<buff<<endl;
            }
        }

    }
    
    return 0;
}