#include<iostream>
#include<unistd.h>
#include <stdio.h>
#include<cstring>
using namespace std;
int rd,wd;
void* c1(void* argv){
	int val;
	while(1){
		cin>>val;
		cout<<"Val Entered in child :"<<val<<endl;
		write(wd,&val,sizeof(int));
		cout<<"Writing in Child:"<<val<<endl;
		sleep(1);
	}
}
void* c2(void* argv){
	int val;
	while(1){
		read(rd,&val,sizeof(int));
		cout<<"Reading in Child:"<<val<<endl;
	}

}
int main(){

	char buf1[1024];
	char buf2[1024];
    rd=dup(STDIN_FILENO);
    wd=dup(STDOUT_FILENO);
    dup2(7,STDIN_FILENO);
	dup2(8,STDOUT_FILENO);
	pthread_t t1,t2;
	pthread_create(&t1,NULL,c1,NULL);
	pthread_create(&t2,NULL,c2,NULL);
	pthread_join(t1,NULL);
	pthread_join(t2,NULL);
	close(rd);
	close(wd);

}
