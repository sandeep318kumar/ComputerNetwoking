// C program to implement one side of FIFO 
// This side reads first, then reads 
#include <stdio.h> 
#include <string.h> 
#include <fcntl.h> 
#include <sys/stat.h> 
#include <sys/types.h> 
#include <unistd.h> 

int main() 
{ 
	int fd1; 

	// FIFO file path 
	char * myfifo = "/tmp/hello"; 

	// Creating the named file(FIFO) 
	// mkfifo(<pathname>,<permission>) 
	mkfifo(myfifo, 0666); 
    fd1 = open(myfifo, O_RDONLY);
    char buff[100];
    read(fd1, buff, 30);
    printf("%s\n", buff);
	// char str1[80], str2[80]; 
	// while (1) 
	// { 
	// 	// First open in read only and read 
	// 	fd1 = open(myfifo,O_RDONLY); 
	// 	read(fd1, str1, 80); 

	// 	// Print the read string and close 
	// 	printf("User1: %s\n", str1); 
	// 	close(fd1); 

	// 	// Now open in write mode and write 
	// 	// string taken from user. 
	// 	fd1 = open(myfifo,O_WRONLY); 
	// 	fgets(str2, 80, stdin); 
	// 	write(fd1, str2, strlen(str2)+1); 
	// 	close(fd1); 
	// } 
	return 0; 
} 


// #include<iostream>
// #include<string.h>
// #include<stdio.h> 
// #include<unistd.h> 
// #include<fcntl.h> 
// #include <stdio.h>
// #include <stdlib.h>
// #include <pthread.h>
// #include <sys/wait.h>
// #include <unistd.h>
// #include <sys/stat.h> 
// #include <semaphore.h>
// #include <sys/types.h>
// #include <fcntl.h>
// using namespace std;

// int main()
// {
//     cout<<"In Reader process\n";
//     char *Hello="/tmp/hello";
//     int cr = mkfifo("Hello", 0666);

//     if(cr == -1){
//         printf("error: %s\n", strerror(errno));
//     }
//     int fd = open("Hello", O_RDONLY);

//     char buff[100];
//     int k = read(fd, buff, 100);
//     buff[k] = '\0';
//     cout<<buff<<endl;
//     close(fd);
//     return 0;
// }