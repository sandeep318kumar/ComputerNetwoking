#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>
#include<stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include<fstream>
#include<sys/wait.h>
int main(){
	char buff[100];
	int a[2],b[2];
	pipe(a);//from parent-> child
	pipe(b);//from child->parent
	pid_t pid =fork();
	if(pid>0){
		close(a[0]);
		scanf("%s",&buff);
		write(a[1],buff,100);
		close(a[1]);
		close(b[1]);
		read(b[0],buff,100);
		printf("%s\n",buff );
		close(b[0]);
	}
	else{
		close(a[1]);
		read(a[0],buff,100);
		int i=0;
		while(buff[i]){
			buff[i]=toupper(buff[i]);
			i++;
		}
		close(b[0]);
		write(b[1],buff,100);
		close(b[1]);
		close(a[0]);
	}
	return 0;
}