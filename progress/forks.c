/*
 * =====================================================================================
 *
 *       Filename:  forks.c
 *
 *    Description:  fork
 *
 *        Version:  1.0
 *        Created:  2011年12月22日 13时11分55秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Yucoat (), thlgood(AT)yucoat.com
 *        Company:  HNUST
 *
 * =====================================================================================
 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main()
{
	pid_t p = 0, k = 1;
	if((p = fork()) < 0)
	{
		perror("fork~");
		exit(EXIT_FAILURE);
	}
	if(p == 0)
	{
		if((k = fork()) < 0)
		{
			perror("fork");
			exit(EXIT_FAILURE);
		}
	}
	printf("p = %d\n", p);
	if(p == 0)
		printf("k = %d\n", k);
	exit(EXIT_SUCCESS);

}
