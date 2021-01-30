#include<iostream>
#include<unistd.h>
#include <stdio.h>
#include<cstring>
#include<fcntl.h>
using namespace std;
int main()
{
	int A[2];
	int B[2];
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
    	dup2(stdi,STDIN_FILENO);
		dup2(stdo,STDOUT_FILENO);
		close(A[0]);
		close(B[1]);
		int cnt=2;
		while(cnt--)
		{
			cout<<"input in parent :";
			cin>>buf1;
			write(A[1],buf1,1024);
			read(B[0],buf2,1024);
			cout<<"Reading in parent: "<<buf2<<endl;
		}
		close(A[1]);
		close(B[0]);
	}
	else{
		execv("./Q4exe",NULL);
	}
	return 0;
}
