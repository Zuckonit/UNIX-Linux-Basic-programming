/*
 * =====================================================================================
 *
 *       Filename:  fork.c
 *
 *    Description:  A sample about fork
 *
 *        Version:  1.0
 *        Created:  2011年12月09日 23时28分06秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Yucoat (), thlgood(AT)yucoat.com
 *        Company:  HNUST
 *
 * =====================================================================================
 */
#include <unistd.h>
#include <stdio.h>
#include <stdarg.h>

int main ( int argc, char *argv[] )
{
	pid_t N;
//	printf("Hello, world\n");

	N = fork();
	if (0 == N)
		printf("Son\n");
	else
		printf("Mother\n");
	if (N)
	{
		printf("Mother is waiting~\n");
		wait(-1);
	}
	if (0 == N)
		printf("Hey~ I'm your son, mother!\n");
	if (N)
		printf("I'm mother\n");
	return 0;
}

