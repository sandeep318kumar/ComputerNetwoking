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

using namespace std;

static struct sigaction sigac;

static void handler(int sig, siginfo_t *siginfo, void* context){
	pid_t sender = siginfo->si_pid;

	if(sig == SIGUSR1){
		cout<<"i am handler, sender is: "<<sender<<endl;
		exit(0);
	}
	return;
}

int main (int argc, char *argv[])
{
    sigac.sa_sigaction = *handler;
	sigac.sa_flags |= SA_SIGINFO;
	if(sigaction(SIGUSR1, &sigac, NULL) != 0){
		cout<<"Error in seigaction\n";
		// return errorno;
	}

    int p1, p2 = getpid();

	mkfifo("/tmp/share", 0666);
	int sfd = open("/tmp/share", O_RDWR);

	char buff[100] = {'\0'};
	read(sfd, buff, 100);
	p1 = stoi(buff);

	sprintf(buff, "%d", p2);
	write(sfd, buff, 100);	

	
	cout<<"Process P1 id is: "<<p1<<"\nProcess P2 id is: "<<p2<<endl;
    kill(p1, SIGUSR2);

	while(1){
		sleep(2);
		cout<<"Hello there\n";
	}
	return 0;
}