#include<stdio.h>
#include<unistd.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>
// int fd;

int main()
{
    printf("Now I am in program 1\n");
    printf("Going to program 2\n");
    int fd = open("dup.txt", O_RDONLY);
    char buff[128];
    read(fd, buff, 50);
    printf("In 1 file: %s\n", buff);
    char *a[] = {"./p2", NULL};
    // execv(a[0], a); 
    return 0;
}