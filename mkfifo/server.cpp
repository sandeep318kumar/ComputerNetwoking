// C program to implement one side of FIFO 
// This side writes first, then reads 
#include <stdio.h> 
#include <string.h> 
#include <fcntl.h> 
#include <sys/stat.h> 
#include <sys/types.h> 
#include <unistd.h> 

int main() 
{ 
	int fd; 

	// FIFO file path 
	char * myfifo = "/tmp/hello"; 

	// Creating the named file(FIFO) 
	// mkfifo(<pathname>, <permission>) 
	mkfifo(myfifo, 0666); 

    fd = open(myfifo, O_WRONLY);
    write(fd, "Hi, there", 30);
	// char arr1[80], arr2[80]; 
	// while (1) 
	// { 
	// 	// Open FIFO for write only 
	// 	fd = open(myfifo, O_WRONLY); 

	// 	// Take an input arr2ing from user. 
	// 	// 80 is maximum length 
	// 	fgets(arr2, 80, stdin); 

	// 	// Write the input arr2ing on FIFO 
	// 	// and close it 
	// 	write(fd, arr2, strlen(arr2)+1); 
	// 	close(fd); 

	// 	// Open FIFO for Read only 
	// 	fd = open(myfifo, O_RDONLY); 

	// 	// Read from FIFO 
	// 	read(fd, arr1, sizeof(arr1)); 

	// 	// Print the read message 
	// 	printf("User2: %s\n", arr1); 
	// 	close(fd); 
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
// // #include <opencv2/opencv.hpp>
// using namespace std;


// int main()
// {
//     cout<<"In writer process\n";
//     char *Hello="/tmp/hello";
//     int cr = mkfifo("Hello", 0666);
//     if(cr == -1){
//         // cout<"Error: "<<*strerror(errno)<<endl;
//         printf("error: %s\n", strerror(errno));
//     }
//     int fd = open("Hello", O_WRONLY);

//     write(fd, "Hi there bro, I am here", 30);
    
//     close(fd);
//     return 0;
// }