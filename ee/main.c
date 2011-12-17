#include "ee.h"

char *LineBuf = NULL;
char Filename[256];
char DstStr[256];

int BufLen = 0;
int Lines = 0;
int DstLine = 1;
int CurLine = 0;


int main(int argc, char *argv[])
{
	int fd;
	char Cbuf;
	InitArgs(argc, argv);

	/* Check file whether exit and creat file description*/
	if ((fd = open(Filename, O_RDONLY)) == -1)
	{
		perror("open");
		return -1;
	}
	
	while ((read(fd, &Cbuf, 1)) > 0)
	{
		if ('\n' != Cbuf)
			PushToBuf(Cbuf);
		else
		{
			CurLine++;
			if(CheckStr(LineBuf, DstStr))
			{
				printf("%d:", CurLine);
				PrintBuf();
				putchar('\n');
			}
			EmptyBuf();
		}
	}
	return 0;
}
