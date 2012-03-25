#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#define PORT	80
#define T_DATA	1
#define T_NAME	2
#define T_COMM	4
#define	T_OTH	8
#define T_END	16

struct pack
{
	char data[1024];	//包含数据
	size_t num;			//编号（0开始）
	size_t datalen;		//data长度
	char type;			//类型	(T_DATA,T_NAME,T_COM, T_OTH)
};

int main(int argc, char *argv[])
{
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

		ssize_t RElen;
		char buf[BUFSIZ];
		char CLName[INET_ADDRSTRLEN];

		FILE *clStream;
		FILE *localFile;
		clStream = fdopen(CLsock, "r");

		struct pack packbuf;
		memset(&buf, 0, sizeof(packbuf));

		if ((CLsock = accept(sock, (struct sockaddr*)&CL, &CLlen)) < 0)
		{
			perror("accept");
			exit(1);
		}
		inet_ntop(PF_INET, &CL.sin_addr.s_addr, CLName, sizeof(CLName));
		printf("Client:%s\t%d\n", CLName, ntohs(CL.sin_port));

		while (fread(&buf, sizeof(struct pack), 1, clStream))
		{
			if(packbuf.type = T_NAME)
			{
				if ((localFile = fopen("localFile", "w")) == NULL)
				{
					perror("fopen");
					break;
				}
			}
			else if(packbuf.type == T_DATA)
			{
				fwrite(packbuf.data, sizeof(char), packbuf.datalen, localFile);
				memset(&packbuf, 0, sizeof(struct pack));
			}
			else if(packbuf.type == T_END)
			{
				fwrite(packbuf.data, sizeof(char), packbuf.datalen, localFile);
				break;
			}
			else
			{
				printf("UNKNOW TYPE!!!\n%d\n", __LINE__);
				exit(1);
			}
		}
		fclose(clStream);
		fclose(localFile);
		close(CLsock);
		printf("Disconnect Client:%s\t%d\n", CLName, ntohs(CL.sin_port));

	}
	return 0;
}
