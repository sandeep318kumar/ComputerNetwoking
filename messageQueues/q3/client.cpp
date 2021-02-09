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
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/wait.h>
#include <sys/stat.h> 
#include <sys/types.h>
#include <sys/mman.h>
#include <sys/resource.h>
using namespace std;

void die(char *s)
{
  perror(s);
  exit(1);
}

struct message_buffer{
	long msg_type;
	char msgtext[1024];
} message;

key_t key = 1234;
int msgid, pid;

void* read_client(void* argv){
    while(1){
        msgrcv(msgid, &message, sizeof(message), pid, 0);
        cout<<message.msgtext<<endl;
    }
}

void* write_client(void* argv){
    while(1){
        message.msg_type = pid;
        
        char buff1[1024] = {'\0'};
        strcpy(message.msgtext, buff1);
        
        cin.getline(message.msgtext, 1024);
        msgsnd(msgid, &message, sizeof(message), 0);
    }
}

int main()
{
    pid = getpid();
    cout<<"Your pid is: "<<pid<<endl;
    msgid = msgget(key, 0666 | IPC_CREAT);
    if(msgid == -1){
		die("msgget");
	}
    cout<<"Message id is: "<<msgid<<endl;

    cout<<"Do you wanna join NITW CSE?\n";
    int x;
    cin>>x;
    if(x == 1){
        char buff[1024] = {'\0'};
        cout<<"Enter your username\n";
        // cin.getline(buff, 1024);
        cin>>buff;
        
        char buff1[1024] = {'\0'};
        strcpy(message.msgtext, buff1);
        
        sprintf(message.msgtext, "%d", pid);
        strcat(message.msgtext, "#");
        strcat(message.msgtext, buff);
        cout<<"Text entered is: "<<message.msgtext<<endl;
        message.msg_type = 1;
        msgsnd(msgid, &message, sizeof(message), 0);

        pthread_t wr, rd;
        pthread_create(&rd, NULL, read_client, NULL);
        pthread_create(&wr, NULL, write_client, NULL);

        pthread_join(wr, NULL);
        pthread_join(rd, NULL);
    }
	
    return 0;
}