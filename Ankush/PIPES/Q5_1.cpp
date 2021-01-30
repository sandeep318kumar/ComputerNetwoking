#include<iostream>
#include<unistd.h>
#include <stdio.h>
#include<cstring>
#include<fcntl.h>
using namespace std;

int A[2];
int B[2];

void* p1(void* argv){
	int val;
	while(1){
		cin>>val;
		cout<<"Val Entered in Parent :"<<val<<endl;
		write(A[1],&val,sizeof(int));
		cout<<"Writing in parent:"<<val<<endl;
		sleep(1);
	}
}
void* p2(void* argv){
	int val;
	while(1){
		read(B[0],&val,sizeof(int));
		cout<<"Reading in Parent:"<<val<<endl;
	}

}
int main()
{
	char buf1[1024];
	char buf2[1024];
	pipe(A);
	pipe(B);
  	int stdi=dup(STDIN_FILENO);
  	int stdo=dup(STDOUT_FILENO);
	dup2(A[0],0);
	dup2(B[1],1);
	int pid=fork();

	if(pid>0)
	{
		pthread_t t1,t2;
		dup2(stdi,STDIN_FILENO);
		dup2(stdo,STDOUT_FILENO);
		close(A[0]);
		close(B[1]);
		pthread_create(&t1,NULL,p1,NULL);
		pthread_create(&t2,NULL,p2,NULL);
		pthread_join(t1,NULL);
		pthread_join(t2,NULL);
	}
	else{
		execv("./a2.out",NULL);
	}
	return 0;
}
