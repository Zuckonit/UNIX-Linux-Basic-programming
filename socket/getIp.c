#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <sys/socket.h>


int queryIp(const char argv[])
{
	struct addrinfo addrC;
	struct addrinfo *addrL;
	struct addrinfo *temp;

	memset(&addrC, 0, sizeof(addrC));
	addrC.ai_family = PF_UNSPEC;
	addrC.ai_socktype = SOCK_STREAM;
	addrC.ai_protocol = IPPROTO_TCP;

	if (getaddrinfo(argv, NULL, &addrC, &addrL) != 0)
	{
		perror("getaddrinfo!");
		freeaddrinfo(addrL);
		return -1;
	}

	for (temp = addrL; temp != NULL; temp = temp->ai_next)
	{
		char addrBuf[BUFSIZ];
		void *addrCount;
		addrCount = &((struct sockaddr_in*)temp->ai_addr)->sin_addr;
		inet_ntop(temp->ai_family, addrCount, addrBuf, BUFSIZ*sizeof(char));
		printf("%s\n", addrBuf);
	}

	freeaddrinfo(addrL);
	return 0;
}

int main(int argc, char *argv[1])
{
	if(argc != 2)
	{
		fputs("lip <domain>\n", stderr);
		exit(1);
	}
	queryIp(argv[1]);
	return 0;
}
