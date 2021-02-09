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

	if(sig == SIGUSR2){
		cout<<"i am handler, sender is: "<<sender<<endl;
		exit(0);
	}
	return;
}
int main (int argc, char *argv[])
{
	sigac.sa_sigaction = *handler;
	sigac.sa_flags |= SA_SIGINFO;
	if(sigaction(SIGUSR2, &sigac, NULL) != 0){
		cout<<"Error in seigaction\n";
		// return errorno;
	}

	int p1 = getpid(), p2;

	mkfifo("/tmp/share", 0666);
	int sfd = open("/tmp/share", O_RDWR);

	char buff[100] = {'\0'};
	sprintf(buff, "%d", p1);
	write(sfd, buff, 100);	

	sleep(1);

	read(sfd, buff, 100);
	p2 = stoi(buff);
	cout<<"Process P1 id is: "<<p1<<"\nProcess P2 id is: "<<p2<<endl;

	kill(p2, SIGUSR1);

	

	while(1){
		sleep(2);
		cout<<"Hello\n";
	}
	return 0;
}