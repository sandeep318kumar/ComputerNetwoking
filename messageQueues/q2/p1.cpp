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
// typedef struct message_buffer message;
int main()
{
	key_t key;
	// key = ftok("progfile", 'B');
	key = 1234;

	int msgid;
	msgid = msgget(key, 0666 | IPC_CREAT);

	if(msgid == -1){
		die("msgget");
	}
	cout<<"Message id is: "<<msgid<<endl;

    while(1){
        msgrcv(msgid, &message, sizeof(message), 1, 0);
        int pp = atoi(message.msgtext);
        
        message.msg_type = pp;
        cout<<"Enter message for "<<pp<<endl;
        cin.getline(message.msgtext, 1024);
        // message.msgtext = "Hi Welcome\n";

        msgsnd(msgid, &message, sizeof(message), 0);
        cout<<"Sent Acknowledge to "<<pp<<endl;
    }

    return 0;
}