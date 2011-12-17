#include "ee.h"

extern char Filename[256];
extern char DstStr[256];
extern int Lines;

/*print help message*/
void Usage()
{
	printf("Usage: ee filename \"string\" +x\n");
}

void InitArgs(int argc, char *argv[])
{
	/*检查参数的个数*/
	if (argc < 4)
	{
		printf("Too less arguments\n");
		Usage();
		exit(EXIT_FAILURE);
	}

	/*检查参数的类型*/
	if (strlen(argv[1]) > 255)
	{
		printf("Filename is too long\n");
		Usage();
		exit(EXIT_FAILURE);
	}

	/* Init args */
	if (argv[1][0] != '+' || argv[1][0] != '-')
	{
		char *temp;
		strncpy(Filename, argv[1], 256);
		strncpy(DstStr, argv[2], 256);
		Filename[255] = '\0';
		DstStr[255] = 0;

		for (temp = &argv[3][1]; *temp != '\0'; temp++)
			Lines = Lines * 10 + (*temp-'0');
		Lines *= argv[2][0] == '+'?1:-1;
	}
}
