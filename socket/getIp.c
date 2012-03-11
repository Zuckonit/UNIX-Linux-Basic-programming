#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <sys/socket.h>
#include <netinet/in.h>

int main(int argc, char *argv[])
{
	struct addrinfo addrC;
	struct addrinfo *addrL;
	struct addrinfo *temp;

	memset(&addrC, 0, sizeof(addrC));
	addrC.ai_family = PF_UNSPEC;
	addrC.ai_socktype = SOCK_STREAM;
//	addrC.ai_protocol = IPPROTO_TCP;

	if (getaddrinfo(argv[1], NULL, &addrC, &addrL) != 0)
	{
		perror("getaddrinfo!");
		exit(1);
	}

	for (temp = addrL; temp != NULL; temp = temp->ai_next)
	{
		char addrBuf[BUFSIZ];
		void *addrCount;
		inet_ntop (temp->ai_family, temp->ai_addr->sa_data, addrBuf, sizeof(char)*BUFSIZ);
		switch (temp->ai_family)
		{
			case AF_INET: 
				addrCount = &((struct sockaddr_in*)temp->ai_addr)->sin_addr;
				break;
			case AF_INET6:
				addrCount = &((struct sockaddr_in6 *)temp->ai_addr)->sin6_addr;
				break;
			default:
				perror("ai_family");
				exit(1);
		}
		inet_ntop(temp->ai_family, addrCount, addrBuf, BUFSIZ*sizeof(char));
		printf("%s\n", addrBuf);
	}
	for (temp = addrL; temp != NULL; temp = addrL)
	{
		addrL = temp->ai_next;
		free(temp);
	}
	return 0;
}
