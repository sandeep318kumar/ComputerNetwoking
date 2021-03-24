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
#include<netinet/in.h>
#include<arpa/inet.h>

using namespace std;

void die(char *s)
{
  	perror(s);
  	exit(1);
}
#define PORT 6000
int main()
{
	cout<<"Hi, my pid is: "<<getpid()<<endl;
	
	int cfd = socket(AF_INET, SOCK_STREAM, 0);

	struct sockaddr_in serveraddress;
	memset(&serveraddress, 0, sizeof(serveraddress));

	serveraddress.sin_family = AF_INET;
	serveraddress.sin_port = htons(PORT);
	serveraddress.sin_addr.s_addr = inet_addr("127.0.0.1");

	if(connect(cfd, (struct sockaddr*)&serveraddress, sizeof(serveraddress)) < 0) die("connect");

	char buff[100] = {'\0'};
	strcpy(buff, "Hello server, I am TCP client.\n");
	write(cfd, buff, 100);
	cout<<"Message from server: ";
	read(cfd, buff, 100);
	cout<<buff<<endl;
	close(cfd);

	return 0;
}