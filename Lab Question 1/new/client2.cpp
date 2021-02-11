#include <iostream>
#include <string.h>
#include <stdio.h> 
#include <unistd.h> 
#include <fcntl.h> 
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <poll.h>
#include <signal.h>
#include <dirent.h>
#include <wait.h> 
#include <sys/wait.h>
#include <sys/stat.h> 
#include <sys/types.h>
#include <sys/mman.h>
#include <sys/resource.h>

using namespace std;

int main()
{
    // cout<<"Hi, I am test file\n";
    char * myfifo = "/tmp/hello"; 
    mkfifo(myfifo, 0666);

    while(1){
        char buff[100];
        cin.getline(buff, 100);
        int fd = open(myfifo, O_WRONLY);
        write(fd, buff, 100);
        sleep(2);
        close(fd);
    }
    return 0;
}