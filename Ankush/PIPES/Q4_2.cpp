#include<iostream>
#include<unistd.h>
#include <stdio.h>
#include<cstring>
using namespace std;
int main(){

	char buf1[1024];
	char buf2[1024];
	int rd,wd;
    rd=dup(STDIN_FILENO);
    wd=dup(STDOUT_FILENO);
	int t=2;
	while(t--)
	{
		read(rd,buf1,1024);
    	dup2(7,STDIN_FILENO);
		dup2(8,STDOUT_FILENO);
    	cout << "Read by child : ";
    	for( int i=0;i<1024;i++)
		{
			if(buf1[i]!='\0')
			{
				cout << buf1[i] ;
			}
			else
			break;
		}
    	cout << endl;
		int i;
		memset(buf2,0,sizeof(buf2));
    	cout << "Enter input from child : ";
		cin >> buf2;
		write(wd,buf2,1024);
	}
	close(rd);
	close(wd);
}
