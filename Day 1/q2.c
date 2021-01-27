#include<stdio.h>
#include<unistd.h>
int main()
{
    printf("Now I am in program 3\n");
    pid_t p1 = fork();
    // printf(p1);
    return 0;
}