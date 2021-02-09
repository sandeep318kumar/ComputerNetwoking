#include <bits/stdc++.h>
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

int msgid;
int n = 0;
// int pids[10];
vector<int> pids;
char usernames[10][1024];

void* readfirst(void* argv){
    cout<<"in read first\n";
    while(1){
        if(msgrcv(msgid, &message, sizeof(message), 1, 0) > 0){
            cout<<"Received this: "<<message.msgtext<<endl;
            int i = 0;
            char buff[1024] = {'\0'};
            while(message.msgtext[i] != '#'){
                buff[i] = message.msgtext[i];
                i++;
            }

            int pp = atoi(buff);
            cout<<"Got this pid: "<<pp<<endl;
            // pids[n] = pp;
            pids.push_back(pp);
            i++;
            memset(buff, '\0', sizeof(buff));
            int j = 0;
            while(message.msgtext[i] != '\0'){
                buff[j] = message.msgtext[i];
                i++;
                j++;
            }
            cout<<"Got this username: "<<buff<<endl;
            // strcpy(usernames[n], buff); 
            // i=0;
            // while(buff[i] != '\0'){
            //     usernames[n][i] = buff[i];
            //     i++;
            // }
            // cout<<"Username is: "<<usernames[n]<<endl;
            n++;
            
            char* welcome = "Welcome to NITW CSE Group";

            char buff1[1024] = {'\0'};
            strcpy(buff1, welcome);

            strcpy(message.msgtext, buff1);
            // cout<<"enter something: ";
            // cin.getline(message.msgtext, 1024);
            message.msg_type = pp;
            
            msgsnd(msgid, &message, sizeof(message), IPC_NOWAIT);
            cout<<"first message sent to: "<<pp<<", message is: "<<message.msgtext<<endl;
            sleep(1);
        }   
    }
}

void* readsecond(void* argv){
    cout<<"in read second\n";
    while(1){
        n = pids.size();
        int gotfrom = 11;
        for(int i=0;i<n;i++){
            if(msgrcv(msgid, &message, sizeof(message), pids[i], IPC_NOWAIT) > 1){
                
                gotfrom = i;
                cout<<"Message received from "<<pids[gotfrom]<<" is: "<<message.msgtext<<endl;
                break;
            }
        }
        
        if(gotfrom != 11){
            cout<<"Total pids are: "<<n<<endl;
            char buff[1024] = {'\0'};
            strcpy(buff, message.msgtext);

            char buff1[1024] = {'\0'};
            strcpy(message.msgtext, buff1);

            sprintf(message.msgtext, "%d", pids[gotfrom]);
            // strcat(message.msgtext, usernames[gotfrom]);
            strcat(message.msgtext, ": ");
            strcat(message.msgtext, buff);

            int i=0;
            while(i < n){
                // if(i != gotfrom){
                    message.msg_type = pids[i];
                    msgsnd(msgid, &message, sizeof(message), 0);
                    cout<<"other message sent to: "<<pids[gotfrom]<<", message is: "<<message.msgtext<<endl;
                    sleep(1);
                // }
                i++;
            }
        }
    }
}

int main()
{
	key_t key = 1234;
	msgid = msgget(key, 0666 | IPC_CREAT);
	if(msgid == -1){
		die("msgget");
	}
	cout<<"Message id is: "<<msgid<<endl;
    memset(usernames, '\0', sizeof(usernames));
    while(1){
        pthread_t read1, read2;
        pthread_create(&read1, NULL, readfirst, NULL);
        pthread_create(&read2, NULL, readsecond, NULL);

        pthread_join(read1, NULL);
        pthread_join(read2, NULL);
    }

    return 0;
}