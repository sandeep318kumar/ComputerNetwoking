#include <iostream>
#include <sys/socket.h>
#include <unistd.h>
#include <netinet/in.h>
#include <fcntl.h>
#include <arpa/inet.h>
#include <poll.h>

using namespace std;

int main()
{
    int sfd1 = socket(AF_INET, SOCK_STREAM, 0);
    int sfd2 = socket(AF_INET, SOCK_STREAM, 0);
    int sfd3 = socket(AF_INET, SOCK_STREAM, 0);
    sockaddr_in my_address, peer_address;
    my_address.sin_family = AF_INET;
    // my_address.sin_addr.s_addr = inet_addr("127.0.0.1");
    my_address.sin_addr.s_addr = INADDR_ANY;

    my_address.sin_port = htons(12000);
    bind(sfd1, (sockaddr *)&my_address, sizeof(my_address));

    my_address.sin_port = htons(12001);
    bind(sfd2, (sockaddr *)&my_address, sizeof(my_address));

    my_address.sin_port = htons(12002);
    bind(sfd3, (sockaddr *)&my_address, sizeof(my_address));

    listen(sfd1, 50);
    listen(sfd2, 50);
    listen(sfd3, 50);

    char buffer[1024];
    int l;

    pollfd fds[3];
    fds[0] = {sfd1, POLLIN, 0};
    fds[1] = {sfd2, POLLIN, 0};
    fds[2] = {sfd3, POLLIN, 0};

    while (1)
    {
        int polls = poll(fds, 3, 500);
        if (polls > 0)
        {
            for (int i = 0; i < 3; ++i)
            {
                if (fds[i].revents)
                {
                    int nsfd = accept(fds[i].fd, (sockaddr *)&peer_address, (socklen_t *)&l);

                    pid_t pid = fork();
                    if (pid > 0)
                    {
                        close(nsfd);
                        fds[i].revents = 0;
                    }
                    else
                    {
                        close(fds[i].fd);
                        dup2(nsfd, 0);
                        dup2(nsfd, 1);
                        string program = "./S" + to_string(i + 1);
                        execl(program.c_str(), program.c_str(), NULL);
                    }
                }
            }
        }
    }
}