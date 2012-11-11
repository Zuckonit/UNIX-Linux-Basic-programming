#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main()
{
    int pipefd[2];
    char buf[BUFSIZ];
    char buf2[BUFSIZ];
    if (pipe(pipefd))
    {
        perror("pipe");
        return 1;
    }
    if (0 == fork())
    {
        if (read(pipefd[0], buf, BUFSIZ) < 0)
        {
            fprintf(stderr, "son process read!\n");
            exit(0);
        }
        printf("From son process:\n");
        printf("%s", buf);
        close(pipefd[0]);
        close(pipefd[1]);
        exit(0);
        
        
    }
    scanf("%s", buf2);
    write(pipefd[1], buf2, sizeof(buf2));
    wait(NULL);
    close(pipefd[0]);
    close(pipefd[1]);
    return 0;
}
