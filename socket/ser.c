/*
 * =====================================================================================
 *
 *       Filename:  ser.c
 *
 *    Description:  A simple TCP/IP message server
 *
 *        Version:  1.0
 *        Created:  2011年12月18日 10时29分35秒
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
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>

void init_daemon()
{
	int pid;
	int i;
	if(pid = fork())
		exit(0);
	else if(pid < 0)
	{
		perror("fork");
		exit(1);
	}
	setsid();
}

int main(int argc, char *argv[])
{
	int sockfd;
	struct sockaddr_in Se;

	if (argc < 2)
	{
		fputs("Too less argument!\n", stderr);
		exit(-1);
	}

	init_daemon();
	freopen("output", "w", stdout);

	memset(&Se, 0, sizeof(Se));
	Se.sin_family = AF_INET;
	Se.sin_addr.s_addr = htonl(INADDR_ANY);
	Se.sin_port = htons(atoi(argv[1]));

	/* Creat socket */
	if ((sockfd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0)
	{
		perror("socket");
		exit(-2);
	}

	/* bind socket */
	if ((bind(sockfd, (struct sockaddr*)&Se, sizeof(Se))) < 0)
	{
		perror("bind");
		exit(-3);
	}

	/* listen */
	if ((listen(sockfd, 5)) < 0)
	{
		perror("listen");
		exit(-4);
	}

	while(1)
	{
		struct sockaddr_in CL;
		int CLLen = sizeof(CL);
		int CLSock;

		if ((CLSock = accept(sockfd, (struct sockaddr*)&CL, &CLLen)) < 0)
		{
			perror("accept");
			exit(-5);
		}
		
		char CLName[INET_ADDRSTRLEN];
		if (inet_ntop(AF_INET, &CL.sin_addr.s_addr, CLName, sizeof(CLName)) != NULL)
			printf("Handling client%s/%d\n", CLName, ntohs(CL.sin_port));
		else
			fputs("Unable to get client address", stderr);

		char buf[BUFSIZ];
		int nBytesRcv;

		if ((nBytesRcv = recv(CLSock, buf, BUFSIZ, 0)) < 0)
		{
			perror("recv");
			exit(-6);
		}
		else
		{
			char i = 0;
			for (i = 0; i < nBytesRcv; i++)
				putchar(buf[i]);
			fflush(stdout);
		}

/*  		while (nBytesRcv > 0)
		{
			int nBytesSen;
			if ((nBytesSen = send(CLSock, buf, nBytesRcv, 0)) < 0)
			{
				perror("send");
				exit(-7);
			}
			else if(nBytesRcv != nBytesSen)
			{
				printf("sent unexpect number bytes");
				exit(-8);
			}
			if ((nBytesRcv = recv(CLSock, buf, BUFSIZ, 0)) < 0)
			{
				perror("recv");
				exit(-9);
			}
			else
			{
				char i = 0;
				for (i = 0; i < nBytesRcv; i++)
					putchar(buf[i]);
			}
		}*/
	}
	return 0;
}
