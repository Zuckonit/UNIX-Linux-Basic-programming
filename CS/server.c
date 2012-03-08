#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#define PORT	80

int main(int argc, char *argv[])
{
/*  	if(argc != 2)
	{
		fputs("Too less argument!\n", stderr);
		exit(1);
	}*/

	int sock;
	struct sockaddr_in SE;
	memset(&SE, 0, sizeof(SE));
	SE.sin_port = htons(PORT);
	SE.sin_family = AF_INET;
	SE.sin_addr.s_addr = htonl(INADDR_ANY);

	sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	if (bind(sock, (struct sockaddr*)&SE, sizeof(SE)) < 0)
	{
		perror("bind");
		exit(1);
	}

	if(listen(sock, 10) < 0)
	{
		perror("listen");
		exit(1);
	}

	while (1)
	{
		struct sockaddr_in CL;
		socklen_t CLlen = sizeof(CL);
		int CLsock;
		char CLName[INET_ADDRSTRLEN];

		if ((CLsock = accept(sock, (struct sockaddr*)&CL, &CLlen)) < 0)
		{
			perror("accept");
			exit(1);
		}
		if(inet_ntop(PF_INET, &CL.sin_addr.s_addr, CLName, sizeof(CLName)) == NULL)
		{
			perror("inet_ntop");
			exit(1);
		}
		else
			printf("Client:%s\t%d\n", CLName, ntohs(CL.sin_port));
	}
	return 0;
}
