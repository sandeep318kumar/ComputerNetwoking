//one way communication using thread and pipe

#include<unistd.h>
#include<stdlib.h>
#include<stdio.h>
#include<pthread.h>
#include<sys/wait.h>
#include<bits/stdc++.h>
using namespace std;

int fd1[2],fd2[2];
void* p1(void* argv){
	int val;
	while(1){
		cin>>val;
		cout<<"Val Entered in Parent :"<<val<<endl;
		write(fd1[1],&val,sizeof(int));
		cout<<"Writing in parent:"<<val<<endl;
		sleep(1);
	}
}
void* p2(void* argv){
	int val;
	while(1){
		read(fd2[0],&val,sizeof(int));
		cout<<"Reading in Parent:"<<val<<endl;
	}

}
void* c1(void* argv){
	int val;
	while(1){
		cin>>val;
		cout<<"Val Entered in child :"<<val<<endl;
		write(fd2[1],&val,sizeof(int));
		cout<<"Writing in Child:"<<val<<endl;
		sleep(1);
	}
}
void* c2(void* argv){
	int val;
	while(1){
		read(fd1[0],&val,sizeof(int));
		cout<<"Reading in Child:"<<val<<endl;
	}

}
int main(){
	if(pipe(fd1)==-1||pipe(fd2)==-1){
		printf("Error in opening pipe" );
		return 0;
	}
	int pid=fork();
	if(pid>0){
		pthread_t t1,t2;
		close(fd1[0]);
		close(fd2[1]);
		pthread_create(&t1,NULL,p1,NULL);
		pthread_create(&t2,NULL,p2,NULL);
		pthread_join(t1,NULL);
		pthread_join(t2,NULL);
	}
	else{
		close(fd2[0]);
		close(fd1[1]);
		pthread_t t1,t2;
		pthread_create(&t1,NULL,c1,NULL);
		pthread_create(&t2,NULL,c2,NULL);
		pthread_join(t1,NULL);
		pthread_join(t2,NULL);
	}
	return 0;
}