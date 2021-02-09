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

int main()
{
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

	msgrcv(msgid, &message, sizeof(message), 3, 0);
	cout<<"Recieved this: "<<message.msgtext<<endl;
	int pp = atoi(message.msgtext);

	msgrcv(msgid, &message, sizeof(message), 3, 0);
	cout<<"Recieved this: "<<message.msgtext<<endl;

	cout<<"Pid is: "<<pp<<endl;
	kill(pp, SIGUSR1);
    return 0;
}