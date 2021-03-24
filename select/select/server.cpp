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

#define PORT 6000

using namespace std;

void die(char *s)
{
  perror(s);
  exit(1);
}

int main()
{
	cout<<"Hi, my pid is: "<<getpid()<<endl;

	struct sockaddr_in server_address, client_address;
	int sfd = socket(AF_INET, SOCK_STREAM, 0);

	bzero(&server_address, sizeof(server_address));

	server_address.sin_family  = AF_INET;
	server_address.sin_addr.s_addr = htonl(INADDR_ANY);
	server_address.sin_port = htons(PORT);

	bind(sfd, (struct sockaddr*)&server_address, sizeof(server_address));
	listen(sfd, 10);

	int ufd = socket(AF_INET, SOCK_DGRAM, 0);
	bind(ufd, (struct sockaddr*)&server_address, sizeof(server_address));
	fd_set rset;

	FD_ZERO(&rset);

	int maxfd = max(ufd, sfd) + 1;

	while(1){
		FD_SET(sfd, &rset);
		FD_SET(ufd, &rset);

		int x = select(maxfd, &rset, NULL, NULL, NULL);

		if(FD_ISSET(sfd, &rset)){
			socklen_t len = sizeof(client_address);
			int nsfd = accept(sfd, (struct sockaddr*)&client_address, &len);
			if(int c = fork() == 0){
				close(sfd);
				char buff[100] = {'\0'};
				cout<<"Message from TCP client is: ";
				if(read(nsfd, buff, 100) == -1) die("read");
				cout<<buff<<endl;
				write(nsfd, "I am server", 100);
				close(nsfd);
				exit(0);
			}
			close(nsfd);
		}

		if(FD_ISSET(ufd, &rset)){
			socklen_t len = sizeof(client_address);
			char buff[100] = {'\0'};
			cout<<"Message from UDP client is: ";
			if(recvfrom(ufd, buff, 100, 0, (struct sockaddr*)&client_address, &len) == -1) die("recvfrom");
			cout<<buff<<endl;
			sendto(ufd, "I am server", 100, 0, (struct sockaddr*)&client_address, sizeof(client_address));
		}
	}

	return 0;
}