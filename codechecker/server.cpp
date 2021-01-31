#include <iostream>
#include <string.h>
#include <stdio.h> 
#include <unistd.h> 
#include <fcntl.h> 
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/wait.h>
#include <unistd.h>
#include <sys/stat.h> 
#include <semaphore.h>
#include <sys/types.h>
#include <fcntl.h>
#include <poll.h>
using namespace std;

int main()
{
    char * myfifo = "/tmp/Code";

    int create = mkfifo(myfifo, 0666);
    if (create == -1)
    {
        printf("error: %s\n", strerror(errno));
    }

    char program[1024] = {'\0'};
    int pip = open(myfifo, O_RDONLY);
    int k = read(pip, program, 1024);
    // program[k] = '\0';
    cout<<"Code is here: "<<program<<endl;
    
    int infd = open("input.txt", O_RDONLY);
    int outfd = open("output.txt", O_RDWR);

    int t1 = dup(0);
    int t2 = dup(1);

    dup2(infd, 0);
    dup2(outfd, 1);

    int pid = fork();
    if(pid > 0){
        sleep(1);

        dup2(t1, 0);
        dup2(t2, 1);

        char test[1024] = {'\0'};
        int tfd = open("test.txt", O_RDONLY);
        read(tfd, test, 1024);

        char out[1024] = {'\0'};
        int ofd = open("output.txt", O_RDONLY);
        read(ofd, out, 1024);

        cout<<"Output you should get: \n";
        cout<<test<<endl;

        cout<<"Output you have got: \n";
        cout<<out<<endl;

        int k = strcmp(test, out);
        cout<<"Str comp is: "<<k<<endl;
        if(k == 0){
            cout<<"WOW!!, You have got correct answer\n";
        } 
        else 
            cout<<"Oops!! incorrect answer\n";
    } else {
        // cout<<
        int pfd = open("p.cpp", O_CREAT | O_WRONLY);

        write(pfd, program, strlen(program));
        chmod("p.cpp", S_IRWXU);
        system("g++ p.cpp -o pa");

        execv("./pa", NULL);
    }

    return 0;
}