#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>

void takeAction(int signalType)
{
	fputs("There is a will, there is a way!\n", stdout);
	exit(1);
}

int main()
{
	struct sigaction handler;
	handler.sa_handler = takeAction;
	if (sigfillset(&handler.sa_mask) < 0)
	{
		perror("sigfillset");
		exit(EXIT_FAILURE);
	}

	if (sigaction(SIGINT, &handler, 0) < 0)
	{
		perror("sigaction");
		exit(EXIT_FAILURE);
	}

	while (1)
	{
		NULL;
	}
	return 0;
}
