#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

int main (int argc, char *argv[])
{
	char *user = NULL;
	user = getenv("USER");
	if(user != NULL)
	{
		puts(user);
	}
	assert(printf("Hello\n"));
	return 0;
}
