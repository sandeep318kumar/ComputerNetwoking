#include <bits/stdc++.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/wait.h>
#include <unistd.h>
//#include <semaphore.h>
#include <sys/types.h>
#include <fcntl.h>
#include <signal.h>
#include <poll.h>
using namespace std;
int main()
{
    struct pollfd fds[3];

    FILE* fp = popen("./e", "r");
    fds[0].fd = fileno(fp);
    fds[0].events = POLL_IN;
    FILE *fp1 = popen("./e1", "r");
    fds[1].fd = fileno(fp1);
    fds[1].events = POLL_IN;
    FILE *fp2 = popen("./e2", "r");
    fds[2].fd = fileno(fp2);
    fds[2].events = POLL_IN;
    int c = 1;
    while(1)
    {
        int retVal = poll(fds, 3, 11000);
        cout<<"Iteration No:"<<c<<endl;
        if(retVal != 0)
        {
            for(int i=0;i<3;i++)
            {
                if(fds[i].revents)
                {
                    char buff[100];
                    read(fds[i].fd,buff,100);   
                    cout<<buff<<":"<<i+1<<endl;
                }
            }
        }
        else
        {
            cout<<"TimeOut"<<endl;
          }
        c++;
    }        
}