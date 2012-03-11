#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

int main(int argc, char *argv[])
{
	int clSock;
	int length;
	int tmp = 0;
	char buf[BUFSIZ];
	char *host = argv[1];
	char GETinfo[BUFSIZ]="GET / HTTP/1.1\r\nHost: ";
	struct sockaddr_in server;

	strcat(GETinfo, host);
	strcat(GETinfo, "\r\nAccept: */*\r\n\r\n");
	clSock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	memset(&server, 0, sizeof(server));
	server.sin_port = htons(80);
	server.sin_family = AF_INET;
	inet_pton(AF_INET, host, &server.sin_addr.s_addr);

	if(connect(clSock, (struct sockaddr*)&server, sizeof(server)) < 0)
	{
		perror("connect");
		exit(1);
	}
	if (send(clSock, GETinfo, sizeof(GETinfo), 0) < sizeof(GETinfo))
	{
		perror("send!");
		exit(1);
	}

	if ((length = recv(clSock, buf, BUFSIZ-1, 0)) < 0)
	{
		perror("recv");
		exit(1);
	}

	buf[length] = '\0';
	printf("%s", buf);

	close(clSock);
	exit(0);
}
