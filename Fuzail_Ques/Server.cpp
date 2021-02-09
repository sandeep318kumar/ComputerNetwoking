#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/wait.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/shm.h>
#include <semaphore.h>
#include <sys/types.h>
#include <fcntl.h>
#include <poll.h>
#include<signal.h>

struct memory {
    int pid;
    int cnt;
};
struct memory* X;


int sw=0;
int pp1[2];
int pp2[2];
char *abc1="/tmp/abc1";
char *abc2="/tmp/abc2";
void handler(int signum)
{
    if(sw==0){
        sw=1;
    }
    else{
        sw=0;
    }
}
void handler2(int signum)
{
    printf("The number of signals are %d\n",X->cnt);
    exit(0);
}
int main()
{
    printf("My pid1 is %d\n",getpid());
    signal(SIGUSR1,handler);
    signal(SIGINT, handler2);
    sleep(1);
    
    pipe(pp1);
    int pid1=fork();
    
    if(pid1 >0)
    {
        pipe(pp2);
        int pid2=fork();
        if(pid2>0)
        {
            mkfifo(abc1,0666);
            mkfifo(abc2,0666);
            
            key_t key=111;
            int shmid=shmget(key,1024,0666|IPC_CREAT);
            int *sem_S1=(int*)shmat(shmid, NULL, 0);
            *sem_S1=0;
            
            key_t key1=222;
            int shmid1=shmget(key1,1024,0666|IPC_CREAT);
            int *sem_S2=(int*)shmat(shmid1, NULL, 0);
            *sem_S2=0;
            
            int key2 = 333;
            int shmid2 = shmget(key2, sizeof(struct memory), IPC_CREAT | 0666);
            X = (struct memory*)shmat(shmid2, NULL, 0);
            X->pid = getpid();
            X->cnt=0;
            
            close(pp1[0]);
            close(pp2[0]);
            
            while(1)
            {
                
                
                int  ffd1=open(abc1, O_RDONLY);
                char arr1[100];
                int k1=read(ffd1,arr1,sizeof(arr1));
                arr1[k1]='\0';
                close(ffd1);
                
                int  ffd2=open(abc2, O_RDONLY);
                char arr2[100];
                int k2=read(ffd2,arr2,sizeof(arr2));
                arr2[k2]='\0';
                close(ffd2);


                if(sw==0)//write in S'
                {
                    write(pp1[1], arr1, strlen(arr1)+1);
                    write(pp2[1], arr2, strlen(arr2)+1);
                    *sem_S1=1;
                    *sem_S2=1;
                    //sw=1;
                }
                else//write in A
                {
                    FILE* pfd1;//A
                    pfd1=popen("./A", "w");
                    fputs(arr1, pfd1);
                    pclose(pfd1);
                    
                    FILE* pfd2;//B
                    pfd2=popen("./B", "w");
                    fputs(arr2, pfd2);
                    pclose(pfd2);
                    
                    //sw=0;
                }
            }
            
            
        }
        else if(pid2==0)
        {
            key_t key=111;
            int shmid=shmget(key,1024,0666|IPC_CREAT);
            int *sem_S1=(int*)shmat(shmid, NULL, 0);
            *sem_S1=0;
            
            key_t key1=222;
            int shmid1=shmget(key1,1024,0666|IPC_CREAT);
            int *sem_S2=(int*)shmat(shmid1, NULL, 0);
            *sem_S2=0;
            
            close(pp2[1]);
            close(pp1[0]);close(pp1[1]);
            while(1)
            {
                while(*sem_S2==0)
                {
                }
                char input_str[100];
               int k1= read(pp2[0], input_str, 100);
                input_str[k1]='\0';
                printf("Read in S'2: %s \n",input_str);
                *sem_S2=0;
                //sleep(1);
            }
            
        }
    }
    else if(pid1==0)
    {
        key_t key=111;
        int shmid=shmget(key,1024,0666|IPC_CREAT);
        int *sem_S1=(int*)shmat(shmid, NULL, 0);
        *sem_S1=0;
        
        close(pp1[1]);
       // close(pp2[0]);close(pp2[1]);
        while(1)
        {
            while(*sem_S1==0)
            {
            }
            char input_str[100];
            int k=read(pp1[0], input_str, 100);
            input_str[k]='\0';
            printf("Read in S'1: %s \n",input_str);
            *sem_S1=0;
            //sleep(1);
        }
        
    }
    
}



