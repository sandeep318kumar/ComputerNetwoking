#include <bits/stdc++.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/wait.h>
#include <unistd.h>
//#include <semaphore.h>
#include <sys/types.h>
#include <fcntl.h>
using namespace std;
int main()
{
    int a[2], b[2];
    char buff[100];
    int fd1=dup(0);
    pipe(a);
    pipe(b);
    int c = fork();
    if (c == 0)
    {
        close(a[1]);
        dup2(a[0],0);
        char buff[10]={"./e1"};
        char* args[]={buff,NULL};
        execvp(args[0],args);
        /*close(b[0]);
        char buff3[100];
        cin.getline(buff3, 100);
        write(b[1], buff3, 100);*/
    }
    else
    {
        close(a[0]);
        int fd2=dup(0);
        dup2(fd1, 0);
        cin.getline(buff, 100);
        dup2(fd2,0);
        //cout<<endl;
        write(a[1], buff, 100);
        /*char buff4[100];
        close(b[1]);
        read(b[0], buff4, 100);
        cout << buff4 << ": Child" << endl;*/

        //cout<<"JAN";
    }
    return 0;
}