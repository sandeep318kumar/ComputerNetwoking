#include <iostream>
#include <string.h>
#include <stdio.h> 
#include <unistd.h> 
#include <fcntl.h> 
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <poll.h>
#include <signal.h>
#include <dirent.h>
#include <wait.h> 
#include <sys/wait.h>
#include <sys/stat.h> 
#include <sys/types.h>
#include <sys/mman.h>
#include <sys/resource.h>
#include <sys/msg.h>
#include <sys/uio.h>
#include<sys/shm.h>

using namespace std;

int main()
{
    struct pollfd fds[3];

    FILE* fp = popen("./p2a", "r");
    fds[0].fd = fileno(fp);
    fds[0].events = POLL_IN;
    FILE* fp1 = popen("./p3a", "r");
    fds[1].fd = fileno(fp1);
    fds[1].events = POLL_IN;
    FILE* fp2 = popen("./p4a", "r");
    fds[2].fd = fileno(fp2);
    fds[2].events = POLL_IN;

    int stdi = dup(STDIN_FILENO);
    int stdo = dup(STDOUT_FILENO);

    int t1, t2;
    dup2(t1, 0);
    dup2(t2, 1);


    int c = fork();
    if(c > 0){
        int c1 = fork();
        if(c1 > 0){
            // p1
            dup2(stdi, STDIN_FILENO);
            dup2(stdo, STDOUT_FILENO);

            while(1){
                int retVal = poll(fds, 3, 10000);
                if(retVal != 0){
                    for(int i=0;i<3;i++){
                        if(fds[i].revents){
                            char buff[100];
                            read(fds[i].fd, buff, 100);   
                            cout<<buff<<":"<<i+1<<endl;
                        }
                    }
                }
            }        
        } else{
            // p5
            execv("./p5a", NULL);
        }
    } else{
        // p6
        wait(NULL);
        execv("./p6a", NULL);
    }
    
    return 0;
}