#include <stdio.h>
#include <sys/socket.h>
#include <string.h>
#include <sys/types.h>
#include <arpa/inet.h>
#define SERVER_PORT	80

int main(int argc, char **argv)
{
	struct sockaddr_in server;
	memset(&server, 0, sizeof(server));
	server.sin_port = htons(SERVER_PORT);
	server.sin_addr.s_addr = htonl()
	
	int sock;
;
	sock = socket()
}
