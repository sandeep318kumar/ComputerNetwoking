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
#include <signal.h>

char *abc2="/tmp/abc2";
int main()
{
    mkfifo(abc2,0666);
    while(1)
    {
        char str1[100];
        int ffd2=open(abc2,O_WRONLY);
        printf("Write to Server\n");
        fgets(str1, 100, stdin);
        write(ffd2,str1,strlen(str1)+1);
        close(ffd2);
    }
}





