#include "hdr.h"

#define PORT 8000
int main(int argc, char const *argv[]) 
{ 
	int sock = 0, valread; 
	struct sockaddr_in serv_addr; 
	char *hello = "Hello from client"; 
	char buffer[1024] = {0}; 
	if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) 
	{ 
		die("socket");
	} 

	serv_addr.sin_family = AF_INET; 
	serv_addr.sin_port = htons(PORT); 
	
	// Convert IPv4 and IPv6 addresses from text to binary form 
	if(inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <= 0) 
	{ 
		printf("\nInvalid address/ Address not supported \n"); 
		return -1; 
	} 

	if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) 
	{ 
		die("connect"); 
	} 
	// while(1){
		char buff[100] = {'\0'};
		cout<<"Write to server\n";
		fflush(stdout);
		cin.getline(buff, 100);

		send(sock , buff , strlen(buff) , 0 ); 
		// printf("message sent\n"); 
		valread = read( sock , buffer, 1024); 
		printf("Read: %s\n",buffer ); 
		fflush(stdout);
		// sleep(2);
	// }
	return 0; 
} 