#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<string.h>
#include<sys/wait.h>
#include <ctype.h>
#include<pthread.h>
int A[2];
int B[2];
char str[100];
char concat_str[100];
char input_str[100];
char output_str[100];
void *p_write_fun(void *vargp)
{
    close(A[0]);
    write(A[1], str, strlen(str)+1);
    close(A[1]);
    return NULL;
}
void *p_read_fun(void *vargp)
{
    close(B[1]);
    read(B[0], concat_str, 100);
    printf("Upper string %s\n", concat_str);
    close(B[0]);
    return NULL;
}
void *c_read_fun(void *vargp)
{
    close(A[1]);
    read(A[0], input_str, 100);
    printf("String read from pipe: %s \n",input_str);
    int k = strlen(input_str);
    int i;
    for (i=0; i<strlen(input_str); i++)
        output_str[i] =toupper(input_str[i]);
    output_str[k] = '\0';
    
    close(A[0]);
    return NULL;
}
void *c_write_fun(void *vargp)
{
    close(B[0]);
    write(B[1], output_str, strlen(output_str)+1);
    close(B[1]);
    return NULL;
}
int main()
{
    
    pthread_t p_read, p_write, c_read, c_write;
    pid_t p;

    pipe(A);
    pipe(B);
    printf("Write lower string\n");
    scanf("%s", str);
    p = fork();
    if(p<0)
    {
        fprintf(stderr, "fork failed");
    }

    if (p > 0)
    {
        
        pthread_create(&p_write, NULL, p_write_fun, NULL);
        pthread_join(p_write, NULL);
        
        wait(NULL);

        pthread_create(&p_read, NULL, p_read_fun, NULL);
        pthread_join(p_read, NULL);
       
    }
    else if(p==0)
    {
        pthread_create(&c_read, NULL, c_read_fun, NULL);
        pthread_join(c_read, NULL);
        
        pthread_create(&c_write, NULL, c_write_fun, NULL);
        pthread_join(c_write, NULL);

        exit(0);
    }
}