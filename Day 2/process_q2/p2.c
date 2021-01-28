#include<stdio.h>
#include<unistd.h>
int main()
{
    printf("Now I am in program 2\n");
    printf("Going to program 1\n");
    char *a[] = {"./p1", NULL};
    execv(a[0], a); 
    return 0;
}