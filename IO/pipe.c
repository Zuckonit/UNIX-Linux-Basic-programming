#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
int main()
{
    int filedes[2];
    pipe(filedes);
    pid_t pid;
    if ((pid = fork()) == 0)
    {
        char buff[64];
        close(filedes[1]);
        read(filedes[0], buff, 64);
        printf("----son----\n%s*\n", buff);
        close(filedes[0]);
        exit(0);
    }
    else
    {
        char buff[] = "hello, world";
        close(filedes[0]);
        write(filedes[1], buff, strlen(buff));
        printf("----father----\n%s*\n", buff);
        close(filedes[1]);
        exit(0);
    }
}
