/******************************************
程序名：	tcpserver
来自：	YUCOAT.COM
功能：	监听某一端口，每当该端口收到数据时，
	该程序将会输出收到的数据打印到控制台上。
日期：	2012-4-7
*******************************************/
#include <stdio.h>
#include <netdb.h>
#include <string.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <unistd.h>
#include <netinet/in.h>

/*return sock*/
int tcp_server_setup(uint16_t port)
{
	int sock;
	struct sockaddr_in ser;
	memset(&ser, 0, sizeof(ser));
	ser.sin_port = htons(port);
	ser.sin_addr.s_addr = htonl(INADDR_ANY);
	ser.sin_family = AF_INET;
	
	/*Create socket*/	
	sock = socket(AF_INET, 		//for IPv4
			SOCK_STREAM,	//sock_stream
			IPPROTO_TCP);	//TCP
	if (sock < 0)
	{
		perror("sock");
		return 1;
	}
	
	/*Bind*/
	if (bind(sock, 
		(struct sockaddr *)&ser, 
		sizeof(ser)) < 0)
	{
		perror("bind");
		return 1;
	}

	/*listen*/
	if (listen(sock, 5) < 0)
	{
		perror("listen");
		return 1;
	}
	return sock;
}

/*Accept from client*/
int accept_cli(int sock)
{
	/*socket & client information*/
	int sock_cli;
	struct sockaddr_in client;
	socklen_t client_sock_len;
	client_sock_len	= sizeof(client);
	
	/*start accept*/
	sock_cli = accept(sock, 
					 (struct sockaddr *)&client, 
					 &client_sock_len);
	if (sock_cli < 0)
	{
		perror("accept");
		return 1;
	}
	return sock_cli;
}

void msg_from_cli(int sock_cli)
{
	char buffer[BUFSIZ + 1];
	int read_len = 0;
	buffer[BUFSIZ] = '\0';
	while (1)
	{
		read_len = read(sock_cli, buffer, BUFSIZ);
		if(read_len < 0)
		{
			perror("read");
			exit(1);
		}
		printf("%s", buffer);
		if(read_len != BUFSIZ)
		{
			close(sock_cli);
			break;
		}
	}
}
int main()
{
	uint16_t port = (uint16_t)atoi("8888");
	int sock = tcp_server_setup(port);
	while (1)
	{
		int sock_cli = accept_cli(sock);
		msg_from_cli(sock_cli);
	}
	return 0;
}
