#include <stdio.h>
#include <stdlib.h>
#include <netdb.h>
#include <arpa/inet.h>

void PrintAddr(const struct sockaddr *addr, FILE *stream);

int main(int argc, char *argv[])
{
	struct addrinfo *HostInfo = NULL, mask, *temp;
	int AddrVal;

	mask.ai_family = AF_UNSPEC;
	mask.ai_socktype = SOCK_STREAM;
	mask.ai_protocol = IPPROTO_TCP;

	if ((AddrVal = getaddrinfo(argv[1], argv[2], &mask, &HostInfo)) != 0)
	{
		perror("getaddrinfo");
		exit(1);
	}
	for(temp = HostInfo; temp != NULL; temp = temp->ai_next)
		PrintAddr(temp->ai_addr, stdout);

	freeaddrinfo(HostInfo);
	return 0;
}

void PrintAddr(const struct sockaddr *addr, FILE *stream)
{
	if(addr == NULL || stream == NULL)
		return;
	void *NumAddr;
	char AddrBuf[INET6_ADDRSTRLEN];
	in_port_t port;

	switch(addr->sa_family)
	{
		case AF_INET:
			NumAddr = &((struct sockaddr_in *) addr)->sin_addr;
			port = ntohs(((struct sockaddr_in *)addr)->sin_port);
			break;
		default:
			fputs("Unknow ", stream);
			return;
	}

	if(inet_ntop(addr->sa_family, NumAddr, AddrBuf, sizeof(AddrBuf)) == NULL)
	{
		fputs("invalid address", stream);
	}
	else
	{
		fprintf(stream, "%s", AddrBuf);
		if(port != 0)
			fprintf(stream, "\t%u\n", port);
	}
}
