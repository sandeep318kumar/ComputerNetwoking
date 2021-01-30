#include <stdio.h>
#include <unistd.h>
#include <string.h>
int main()
{
    write(1,"p4",1024);
    return 0;
}