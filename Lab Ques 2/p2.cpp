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

void die(char *s)
{
  perror(s);
  exit(1);
}

struct message_buffer{
    long msg_type;
    char msgtext[100];
} message;

void handler(int sig){
    cout<<"Recieved this signal: "<<sig<<endl;
}

long p2;
long A[2];
int msgid;

void* wrt(void* argv){
    while(1){
        cout<<"Write to Other processes: ";
        char buff[1024] = {'\0'};
        sprintf(buff, "%d", p2);
        strcat(buff, ":");

        char buff1[1024] = {'\0'};
        cin.getline(buff1, 1024);
        strcat(buff, buff1);

        message.msg_type = A[0];
        strcpy(message.msgtext, buff);
        if(msgsnd(msgid, &message, sizeof(message)+1, 0) == -1)
            die("msgsnd");
        sleep(1);
        
        message.msg_type = A[1];
        strcpy(message.msgtext, buff);
        if(msgsnd(msgid, &message, sizeof(message)+1, 0) == -1)
            die("msgsnd");
        sleep(1);
    }
}

void* r1(void* argv){
    while(1){
        if(msgrcv(msgid, &message, sizeof(message)+1, p2, 0) == -1)
            die("msgrcv");
        cout<<"Read this: "<<message.msgtext<<endl;
        sleep(1);
    }
}
void printinfo(){
	struct msqid_ds buf;
	msgctl(msgid, IPC_STAT, &buf);
	// cout << "Message Queue *Permission* Structure Information" << endl;
	cout << "Current No. of messages on queue: " << buf.msg_qnum << endl;
	// cout << "Maximum No. of bytes on queue 	" << buf.msg_qbytes << endl;
}
int main()
{
    cout<<"Hi, my pid is: "<<getpid()<<endl;
    signal(SIGUSR1, handler);

    // for message queue
    key_t key;
    key = 12345;

    msgid = msgget(key, 0666 | IPC_CREAT);

    if(msgid == -1){
        die("msgget");
    }
    cout<<"Message id is: "<<msgid<<endl;
    
    sem_t *s = sem_open("/s",   O_CREAT | O_RDWR, 0660, 0);
    sem_t *s2 = sem_open("/s2", O_CREAT | O_RDWR, 0660, 0);

    // for getting pids of other processes
    p2 = getpid();
    memset(A, 0, sizeof(A));
    int cnt = 0;

    message.msg_type = p2;
    if(msgsnd(msgid, &message, sizeof(message)+1, 0) == -1)
        die("msgsnd");
    if(msgsnd(msgid, &message, sizeof(message)+1, 0) == -1)
        die("msgsnd");
    if(msgsnd(msgid, &message, sizeof(message) + 1, 0) == -1)
        die("msgsnd");

    cout<<"Sent messages\n";
    int pid = getpid();
    while(1){
        if(msgrcv(msgid, &message, sizeof(message)+1, 0, MSG_NOERROR) == -1)
            die("msgrcv");
        
        long r = message.msg_type;
        if(r != pid){
            if(cnt == 0){
                A[0] = r;
                cnt++;
            } else if(cnt == 1){
                if(r == A[0]){
                    message.msg_type = pid;
                    if(msgsnd(msgid, &message, sizeof(message)+1, 0) == -1)
                        die("msgsnd");
                } else {
                    A[1] = message.msg_type;
                    cnt++;
                }
            }
        } else{
            message.msg_type = pid;
            if(msgsnd(msgid, &message, sizeof(message)+1, 0) == -1)
                die("msgsnd");
        }
        if(cnt == 2){
            message.msg_type = pid;
            if(msgsnd(msgid, &message, sizeof(message)+1, 0) == -1)
                die("msgsnd");
            break;
        }
    }
    sem_post(s);

    cout<<"Process ids are:";
    cout<<"\nP1: "<<A[0];
    cout<<"\nP2: "<<pid;
    cout<<"\nP3: "<<A[1]<<endl;

    // after getting the signal from process f
    sem_wait(s2);
    cout<<"Now I can send messages\n";
    pthread_t wr, rd;
    pthread_create(&wr, NULL, wrt, NULL);
    pthread_create(&rd, NULL, r1, NULL);

    pthread_join(wr, NULL);
    pthread_join(rd, NULL);

    return 0;
}