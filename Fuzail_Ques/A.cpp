
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<string.h>
#include<sys/wait.h>

int main()
{
    char input_str[100];
    int k=read(0, input_str, 100);
    input_str[k]='\0';
    printf("String read from pipeA: %s \n",input_str);
    
    exit(0);
}
