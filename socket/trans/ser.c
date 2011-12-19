/*
 * =====================================================================================
 *
 *       Filename:  ser.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2011年12月19日 19时54分00秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Yucoat (), thlgood(AT)yucoat.com
 *        Company:  HNUST
 *
 * =====================================================================================
 */
#include <sys/socket.h>
#include <unistd.h>
#include <stdio.h>
#include <netinet/in.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>

#define _SER_PORT_ 98

char *savefile = "out";

int main(int argc, char *argv[])
{
	int Sersock, Clisock;
	int filefd, nByte;
	char buf[BUFSIZ];
	struct sockaddr_in SerInfo, CliInfo;

/*  	if (argc < 2)
	{
		fputs("Too less argument!\n", stderr);
		exit(1);
	}
*/
	memset(&SerInfo, 0, sizeof(SerInfo));
	SerInfo.sin_port = htons(_SER_PORT_);
	SerInfo.sin_family = AF_INET;
	SerInfo.sin_addr.s_addr = htonl(INADDR_ANY);

	filefd = open(	savefile, 
			O_WRONLY|O_CREAT|O_APPEND, 
			S_IRUSR|S_IWUSR|S_IRGRP|S_IWGRP|S_IROTH);
	if(filefd < 0)
	{
		perror("open");
		exit(1);
	}

	if ((Sersock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
	{
		perror("socket");
		exit(1);
	}

	/* Bind the socket with port */
	if (bind(Sersock, (struct sockaddr*)&SerInfo, sizeof(SerInfo)) < 0)
	{
		perror("bind");
		exit(1);
	}

	/* listen */
	if((listen(Sersock, 5)) < 0)
	{
		perror("listen");
		exit(1);
	}

	while (1)
	{
		int CliLen = sizeof(CliInfo);
		if((Clisock = accept(Sersock, (struct sockaddr*)&CliInfo, &CliLen)) < 0)
		{
			perror("accept");
			exit(1);
		}
		while (1)
		{
			if ((nByte = recv(Clisock, buf, BUFSIZ, 0)) < 0)
			{
				perror("recv");
				exit(1);
			}
			if (write(filefd, buf, nByte) != nByte)
			{
				perror("write");
				exit(1);
			}
			if (nByte != BUFSIZ)
			{
				close(filefd);
				break;
			}
		}
	}
	return 0;
}
