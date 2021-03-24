#include "hdr.h"

#define PORT 8000
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
	if((sfd = socket(AF_INET, SOCK_STREAM, 0)) == 0) { 
		die("socket"); 
	} 
	
	if (setsockopt(sfd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) { 
		die("setsockopt"); 
	} 

	address.sin_family = AF_INET; 
	address.sin_addr.s_addr = INADDR_ANY; 
	address.sin_port = htons( PORT ); 
	
	if(bind(sfd, (struct sockaddr *)&address, sizeof(address))<0) { 
		die("bind"); 

	} 
	while(1){
		if (listen(sfd, 3) < 0) { 
			die("listen"); 
		} 
		if ((nsfd = accept(sfd, (struct sockaddr *)&address, (socklen_t*)&addrlen)) < 0) { 
			die("accept"); 
		} 
		
		cout << "\nAccepting at " <<  nsfd << " \n";
		fflush(stdout);
		
		cout<<"forking now\n";
		int pid = fork();
		if(pid == 0){
			close(sfd);
			cout<<"I am child\n";
			int rnsfd1 = dup(nsfd);
			dup2(rnsfd1, 0);
			// int rnsfd2 = dup(nsfd);
			// dup2(rnsfd2, 1);
			execv("./a", NULL);
		}
		else{
			cout<<"I am parent\n";
			close(nsfd);
			wait(NULL);
		}
		sleep(1);
		wait(NULL);
	}	
	return 0;
}