#include "hdr.h"

#define PORT 8080 
int main()
{
	dup2(STDOUT_FILENO, 8);
	// FILE* STDOUT_FILENO = dup(8);
	cout<<"output: "<<STDOUT_FILENO<<endl;
	cout<<"Hi, my pid is: "<<getpid()<<endl;

	int nsfd;
	nsfd = dup(0);

	dup2(STDIN_FILENO, 7);

	char buffer[100] = {'\0'};
	int valread = read(0 , buffer, 1024); 
	printf("Read this: %s\n",buffer ); 
	fflush(stdout);

	char buff[100] = {'\0'};
	cout<<"Write to client\n";
	// cin.getline(buff, 100);
	strcpy(buff, "Hello client\n");

	send(nsfd , buff , strlen(buff) , 0 ); 
	printf("message sent\n");
	fflush(stdout);
	// sleep(1.9);

	return 0;
}