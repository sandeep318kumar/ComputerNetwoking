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
    char buff2[100];
    cin.getline(buff2,100);
    cout << buff2 << ": Parent" << endl;
    return 0;
}