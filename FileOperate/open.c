/*
 *title:	a sample program about fcntl.h/open()
 *
 *author:	yucoat thlgood(AT)yucoat.com www.yucoat.com
 *
 *date:		6 Dec 2011
 *
 *version:	0.1
 *
 *log:		NULL
 */

#include <stdio.h>		// for IO
#include <fcntl.h>		//for open()
#include <stdlib.h>		//for exit()
#include "thlgood.h"

int main(int argc, char *argv[])
{
	int count;
	int fd;			//file descript
	if (argc < 2)
	{
		printf("Arguments is too less !\n");
		exit(0);
	}

	if ((fd = open(argv[count], O_RDONLY)) == -1)
		printf("No!, file not exist\n");
	else
	{
		printf("Yes, file exist!\n", fd);
		close(fd);
	}

	return 0;
}


