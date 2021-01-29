#include<iostream>
#include<string.h>
#include<stdio.h> 
#include<unistd.h> 
#include<fcntl.h> 
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/wait.h>
#include <unistd.h>
#include <semaphore.h>
#include <sys/types.h>
#include <fcntl.h>
using namespace std;


int main(int argc, char* argv[])
{
    char buff[1024];
    cin.getline(buff, 1024);
    cout<<"From Parent: "<<buff<<endl;
    // cout<<argv<<endl;
    // close(B[0]);
    // close(A[1]);

    // while(1){

    //     int bytesread = read(A[0], buff, 1024);
    //     buff[bytesread] = 0;
            
    //     cout<<"From Parent: "<<buff<<endl;

    //     cout<<"Type your message to Parent: ";
    //     cin.getline(buff, 30);
    //     write(B[1], buff, strlen(buff));
    // }
    return 0;
}