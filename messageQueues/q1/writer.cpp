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

int main()
{
	key_t key;
	// key = ftok("progfile", 'B');
	key = 1234;

	msgid = msgget(key, 0666 | IPC_CREAT);
	if(msgid == -1){
		die("msgget");
	}
	cout<<"Message id is: "<<msgid<<endl;

	message.msg_type = 1;
	cout<<"Enter some data\n";
	while(cin.getline(message.msgtext, 1024)){
		if(msgsnd(msgid, &message, sizeof(message), 0) == -1){
			perror("msgsnd");
			exit(1);
		}
		else cout<<"Message sent\n";
	}
    return 0;
}