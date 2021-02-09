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
int msgid;

void printinfo(){
	struct msqid_ds buf;
	msgctl(msgid, IPC_STAT, &buf);
	cout << "Message Queue *Permission* Structure Information" << endl;
 	cout << "Owner's user ID 	" << buf.msg_perm.uid << endl;
	cout << "Creator's user ID 	" << buf.msg_perm.cuid << endl;
	cout << "Current No. of messages on queue	" << buf.msg_qnum << endl;
	cout << "Maximum No. of bytes on queue 	" << buf.msg_qbytes << endl;
}
int cnt = 0;

void handler(int sig){
    if(sig == SIGUSR1){
        cout<<"Increasing count: "<<cnt<<endl;
        cnt++;
    }
}

int main()
{
    cout<<"Pid is: "<<getpid()<<endl;

    signal(SIGUSR1, handler);

	key_t key;
    int kk;
    cout<<"enter key: ";
    cin>>kk;
	key = kk;

	msgid = msgget(key, 0666 | IPC_CREAT);
	if(msgid == -1){
		die("msgget");
	}
	cout<<"Message id is: "<<msgid<<endl;

    // for p2;
    message.msg_type = 2;
    sprintf(message.msgtext, "%d", getpid());
    msgsnd(msgid, &message, sizeof(message), 0);

    message.msg_type = 2;
    strcpy(message.msgtext, "Hello P2, I am P1");
    msgsnd(msgid, &message, sizeof(message), 0);

    message.msg_type = 2;
    strcpy(message.msgtext, "Hello P2, How are you?");
    msgsnd(msgid, &message, sizeof(message), 0);

    message.msg_type = 2;
    strcpy(message.msgtext, "Hello P2, Happy Coding!");
    msgsnd(msgid, &message, sizeof(message), 0);



    // for p3
    message.msg_type = 3;
    sprintf(message.msgtext, "%d", getpid());
    msgsnd(msgid, &message, sizeof(message), 0);

    message.msg_type = 3;
    strcpy(message.msgtext, "Hello P3, How are you?");
    msgsnd(msgid, &message, sizeof(message), 0);

    message.msg_type = 3;
    strcpy(message.msgtext, "Hello P3, I hope all is well there");
    msgsnd(msgid, &message, sizeof(message), 0);

    message.msg_type = 3;
    strcpy(message.msgtext, "Hello P3, Happy Coding");
    msgsnd(msgid, &message, sizeof(message), 0);

    printinfo();

    while(1){
        if(cnt == 2){
            cnt = 0;
            printinfo();
        }
    }
    return 0;
}