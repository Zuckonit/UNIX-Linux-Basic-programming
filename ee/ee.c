/*
 * =====================================================================================
 *
 *       Filename:  ee.c
 *
 *    Description:  Find some text in a ASCII file
 *
 *        Version:  1.0
 *        Created:  2011年12月15日 20时58分22秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Yucoat (), thlgood(AT)yucoat.com
 *        Company:  HNUST
 *
 * =====================================================================================
 */
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
int	dst_lines = 1;
int	lines = 1;
char	filename[256];	//file name length limit
int	fd;

char	*line_buf;

void Usage()
{
	printf("Usage: ee filename \"string\" +x\n");
}

void check_args_and_init(int argc, char *argv[])
{

	if (argc != 4 || strlen(argv[2]) > 255)
	{
		Usage();
		exit(-1);
	}

	/* Init args */
	if (argv[1][0] != '+' || argv[1][0] != '-')
	{
		char *temp;
		strncpy(filename, argv[1], 256);
		filename[255] = '\0';

		for (temp = &argv[2][1]; *temp != '\0'; temp++)
			lines = lines * 10 + (*temp-'0');

		lines *= argv[2][0] == '+'?1:-1;
	}
}

bool push_to_line_buf(char s)
{
	while
}

int main(int argc, char *argv[])
{

	unsigned long 	dst_line = 1;
	char		temp;
	char		*dst_string = argv[3];
	int		str_len = strlen(argv[3]);
	int		stack = 0;

	check_args_and_init(argc, argv);
	dst_string = argv[3];

	/* Check file whether exit and creat file description*/
	if ((fd = open(filename, O_RDONLY)) == -1)
	{
		perror("open");
		return -1;
	}

	while ((read(fd, &temp, 1)) > 0)
	{
		if (temp == '\n')
		{
			dst_lines++;
			if(dst_string[stack] == ' ')
			{	
				stack++;
				if (stack == str_len)
					break;
				else
				{
					continue;
				}
			}
			else
				stack = 0;
		}
		else
		{
			if (temp == dst_string[stack])
			{
				stack++;
				if (stack==str_len)
					break;
				else
				{
					continue;
				}
			}
			else
			{
				stack = 0;
			}
		}
	}
	if(stack == str_len)	/* whether we find the string */
	{
		printf("Yes, I found it: %d\n", dst_lines);
	}
	return 0;
}
