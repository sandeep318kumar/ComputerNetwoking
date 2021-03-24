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
#include <sys/shm.h>
#include <sys/socket.h> 
#include <arpa/inet.h> 
#define PORT 8080 

using namespace std;

void die(char *s)
{
	perror(s);
  	exit(1);
}

int main()
{
	cout<<"Hi, my pid is: "<<getpid()<<endl;

	int sfd, nsfd, valread; 
	struct sockaddr_in address; 
	int opt = 1; 
	int addrlen = sizeof(address); 
	char buffer[1024] = {0}; 
	char *hello = "Hello from server"; 
	
	// Creating socket file descriptor  
	if ((sfd = socket(AF_INET, SOCK_STREAM, 0)) == 0) { 
		die("socket"); 
	} 
	
	if (setsockopt(sfd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) { 
		die("setsockopt"); 
	} 

	address.sin_family = AF_INET; 
	address.sin_addr.s_addr = INADDR_ANY; 
	address.sin_port = htons( PORT ); 
	
	if (bind(sfd, (struct sockaddr *)&address, sizeof(address))<0) { 
		die("bind"); 

	} 
	while(1){
		if (listen(sfd, 3) < 0) { 
			die("listen"); 

		} 
		if ((nsfd = accept(sfd, (struct sockaddr *)&address, (socklen_t*)&addrlen)) < 0) { 
			die("accept"); 

		} 

		valread = read( nsfd , buffer, 1024); 
		printf("Read this: %s\n",buffer ); 

		char buff[100] = {'\0'};
		cout<<"Write to client\n";
		cin.getline(buff, 100);
		send(nsfd , buff , strlen(buff) , 0 ); 
		printf("message sent\n");
		// sleep(1.9);
	}
	
	return 0;
}