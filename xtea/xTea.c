/*
 * =====================================================================================
 *
 *       Filename:  xTea.c
 *
 *    Description:  a simple encryption with xtea
 *
 *        Version:  1.0
 *        Created:  2011年12月21日 22时06分46秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Yucoat, thlgood(AT)yucoat.com
 *        Company:  HNUST
 *
 * =====================================================================================
 */
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <polarssl/xtea.h>


int main(int argc, char *argv[])
{
	xtea_context xc;
	int in_fd, out_fd;
	int len, mod;
	unsigned char in_buf[8], out_buf[8];
	unsigned char iv[8] = "1234567";

  	if(argc != 5)
	{
		printf("xtea input output <key> <mod>\n");
		exit(EXIT_FAILURE);
	}

	mod = (argv[4][0] == '0')?XTEA_DECRYPT:XTEA_ENCRYPT;
//	printf("mod = %d\n", mod);

	xtea_setup(&xc, argv[3]);
	if ((in_fd = open(argv[1], O_RDONLY)) < 0)
	{
		perror("open");
		exit(EXIT_FAILURE);
	}
  	if((out_fd=open(argv[2], 
			O_WRONLY|O_CREAT|O_EXCL, 
			S_IRUSR|S_IWUSR|S_IRGRP|S_IWGRP|S_IRGRP)) < 0)
	{
		perror("open");
		exit(EXIT_FAILURE);
	}
	while ((len = read(in_fd, in_buf, 8)) > 0)
	{
		char tmp[8]; 
		while (len++ < 8) in_buf[len-1] = '\0';
		
		if (xtea_crypt_ecb(&xc, mod, in_buf, out_buf) != 0)
		{
			printf("Error, in buf len\n");
			exit(EXIT_FAILURE);
		}

		if(mod)
		{
			write(out_fd, out_buf, 8);
			write(0, out_buf, 8);
		}
		else 
		{
			if(tmp[7] == '\0')
				write(out_fd, out_buf, strlen(out_buf));
			else
				write(out_fd, out_buf, 8);
		}
	}

	close(in_fd);
	close(out_fd);
	return 0;
}
