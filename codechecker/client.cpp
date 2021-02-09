#include <iostream>
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
using namespace std;

int main()
{
    char * myfifo = "/tmp/Code";

    int create = mkfifo(myfifo, 0666);
    if (create == -1)
    {
        printf("error: %s\n", strerror(errno));
    }
    int pip = open(myfifo, O_WRONLY);

    int fd = open("sol.cpp", O_RDONLY);

    char buff[1024] = {'\0'};
    int k = read(fd, buff, 1024);
    buff[k] = '\0';
    write(pip, buff, 1024);

    return 0;
}