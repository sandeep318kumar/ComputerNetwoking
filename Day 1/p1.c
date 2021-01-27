#include<stdio.h>
#include<unistd.h>
int main()
{
    printf("Now I am in program 1\n");
    printf("Going to program 2\n");
    const char *a[] = {"./p2", NULL};
    execv(a[0], a); 
    return 0;
}