#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main()
{
	int status;
	pid_t p = 0, k = 1;
	if((p = fork()) < 0)
	{
		perror("fork~");
		exit(EXIT_FAILURE);
	}
	if(p != 0)
	{
		wait(&status);
	}
	if(p != 0)
	{
		printf("I'm father!\n");
	}
	else
	{
		printf("I'm son!\n");
		exit(EXIT_SUCCESS);
	}
	exit(EXIT_SUCCESS);

}
