#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>
#include<stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include<fstream>

int main(){
	char buff[100],buff1[100];
	int pp[2];
	pipe(pp);
	scanf("%s",&buff);
	write(pp[1],buff,100);
	read(pp[0],buff1,100);
	printf("%s\n",buff1 );
	return 0;
}