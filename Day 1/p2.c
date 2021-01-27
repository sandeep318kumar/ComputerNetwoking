#include<stdio.h>
#include<unistd.h>
int main()
{
    printf("Now I am in program 2\n");
    printf("Going to program 3\n");
    const char *a[] = {"./p3", NULL};
    execv(a[0], a); 
    return 0;
}