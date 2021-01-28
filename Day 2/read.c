#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    int fd;
    char buff[128];
    fd = open("in.txt", O_RDONLY);
    int c = fork();

// to read line by line
    // while (1)
    // {
    //     char buf1[1];
    //     if(c > 0){
    //         printf("Parent Word: ");
    //         while(read(fd, buff, 1) != ' '){
    //             printf("%s", buff);
    //         }
    //     } else
    //     {
    //         printf("Parent Word: ");
    //         while(read(fd, buff, 1) != ' '){
    //             printf("%s", buff);
    //         }
    //     }
    //     if(read(fd, buff, 1) == 0) break; 
    // }
    


// read 10 in parent and 10 char in child
   while( read(fd, buff, 10) > 0) {
    //    read(fd, buff, 10);
       if(c > 0){
            // printf("Parent printing\n");
            printf("Parent: %s\n", buff);
        } else
        {
            // printf("child printing\n");
            printf("child: %s\n", buff);   
        }
   }
   
  return 0;
}