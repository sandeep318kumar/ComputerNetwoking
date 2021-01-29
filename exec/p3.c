#include<stdio.h>
#include<unistd.h>
int main()
{
    printf("Now I am in program 3\n");
    printf("Going to program 4\n");
    char *a[] = {"./p4", NULL};
    execv(a[0], a); 
    return 0;
}