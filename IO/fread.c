#include <stdio.h>

#define CLEAR_INPUT_BUFFER__	setbuf(stdin, NULL);
#define FLUSH_IO__				fflush(NULL);

int main()
{
	char name[20];
	char email[20];
	scanf("%s", name);
	printf("%s\n", name);
	setbuf(stdin, NULL);
	scanf("%s", email);
	printf("%s\n", email);
	return 0;
}
