/*
 * =====================================================================================
 *
 *       Filename:  cli.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2011年12月19日 21时12分45秒
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
#include <string.h>
#include <fcntl.h>
#include <netinet/in.h>
#include <sys/stat.h>
#include <arpa/inet.h>
#include <unistd.h>

#define _PORT_ 98

char *SerIP = "127.0.0.1";
char *File;
int main(int argc, char *argv[])
{
	int Clisock, Sersock;
	struct sockaddr_in SerInfo, CliInfo;
	int filefd, nByte;
	char buf[BUFSIZ];

	if(argc < 2)
	{
		fputs("Too less arguments!\n", stderr);
		exit(1);
	}
	memset(&CliInfo, 0, sizeof(CliInfo));
	File = argv[1];

	SerInfo.sin_family = AF_INET;
	SerInfo.sin_addr.s_addr = inet_addr(SerIP);
	SerInfo.sin_port = htons(_PORT_);

	if ((Clisock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
	{
		perror("scoket");
		exit(1);
	}

	if(connect(Clisock, (struct sockaddr*)&SerInfo, sizeof(SerInfo)) < 0)
	{
		perror("connect");
		exit(1);
	}
	while (1)
	{
		filefd = open(File, O_RDONLY);
		while((nByte = read(filefd, buf, BUFSIZ)) > 0)
		{
			if(send(Clisock, buf, nByte, 0) < 0)
			{
				perror("send");
				exit(1);
			}
			if(nByte < BUFSIZ)
			{
				send(Clisock, "END", 3, 0);
				break;
			}

		}
		send(Clisock, "END", 3, 0);
		break;
	}
	close(Clisock);
	close(filefd);
	return 0;
}
