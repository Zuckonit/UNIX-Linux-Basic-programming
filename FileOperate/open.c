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
#include <unistd.h>
#include <string.h>
#include <sys/stat.h>
#include <stdlib.h>		//for exit()

int main(int argc, char *argv[])
{
	int count;
	int fd;			//file descript
	char Msg[] = "Hello, World!\n";

	/* check the count of argc */
	if (argc < 3)
	{
		printf("Arguments is too less !\n");
		exit(0);
	}
 
	/* dectect if a file exists */
	if ((fd = open(argv[count], O_RDONLY)) == -1)
		printf("No!, file not exist\n");
	else
	{
		printf("Yes, file exist!\n", fd);
		close(fd);
	}
	//close file descript;
	close(fd);

	/* creat a file */

	/*-----------------------------------------------------------------------------
	 *  With O_EXCL:if file exist , open() will return -1
	 *  without O_EXCL:if file not exist , file will be creat!
	 *-----------------------------------------------------------------------------*/
	if ( (fd = open(argv[2], 					//Filename
			O_RDWR|O_CREAT|O_EXCL, 				//model
			S_IRUSR|S_IWUSR|S_IRGRP|S_IROTH)) == -1)	//access
	{
		perror("Open");
		exit(EXIT_FAILURE);
	}

	/* file created successful, write some info into it! */
	else if ((write(fd, Msg, strlen(Msg))) != strlen(Msg)) 
	{
			perror("Write Msg failure!");
			exit(EXIT_FAILURE);
	}
	

	close(fd);
	return 0;
}


