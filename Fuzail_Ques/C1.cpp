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
#include <semaphore.h>
#include <sys/types.h>
#include <fcntl.h>
#include <poll.h>
#include<signal.h>

char *abc1="/tmp/abc1";
int main()
{
    mkfifo(abc1,0666);
    while(1)
    {
        char str1[100];
        int ffd1=open(abc1,O_WRONLY);
        printf("Write to Server\n");
        fgets(str1, 100, stdin);
        write(ffd1,str1,strlen(str1)+1);
        close(ffd1);
    }
}



