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

int main()
{   
    char * myfifo = "/tmp/NITW"; 
	mkfifo(myfifo, 0666); 
    int mfd = open(myfifo, O_RDWR);

    int users[10];
    int n = 0;
    while(1){
        char buff1[1024] = {'\0'};
        read(mfd, buff1, 1024);
        // cout<<"User wrote this: "<<buff1<<endl;
        if(buff1[0] == '#'){
            char userid[1024] = {'\0'};
            int i=1, j = 0;
            while(i < strlen(buff1)){
                userid[j++] = buff1[i++];
            }

            char ufifo[100] = {'\0'};

            char* userfifo = "/tmp/";
            strcpy(ufifo, userfifo);
            strcat(ufifo, userid);
            cout<<"User fifo is: "<<ufifo<<endl;

            int cr = mkfifo(ufifo, 0666);
            if(cr < 0){
                printf("Error: %s\n", stderr);
            }
            int ufd = open(ufifo, O_RDWR);
            
            write(ufd, "Welcome to NITW", 100);
            cout<<userid<<" This person has joined\n";
            users[n] = ufd;
            n++;
        } else {
            char userchat[1024] = {'\0'};
            char userid[1023] = {'\0'};
            int i = 0, j = 0;
            while(i < strlen(buff1) && buff1[i] != '#'){
                userid[j] = buff1[i];
                j++;
                i++;
            }
            j = 0;
            i++;
            while(i < strlen(buff1)){
                userchat[j++] = buff1[i++];
            }
            cout<<"@"<<userid<<" User wrote this: "<<userchat<<endl;
            char message[1024] = {'\0'};
            strcat(message, "@");
            strcat(message, userid);
            strcat(message, ": ");
            strcat(message, userchat);
            for(int k = 0;k<n;k++){
                // cout<<"users\n";
                write(users[k], message, 1024);
            }
        }
        memset(buff1, '\0', sizeof(buff1));
    }
    return 0;
}