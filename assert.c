#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>

typedef struct
{
	char name[20];
	bool sex;
	char addr[40];
}Personinfo;

int main(int argc, char *argv[])
{
	Personinfo *p = NULL;
	p = malloc(sizeof *p);
	assert(p != NULL);
	free(p);
	p = NULL;
	exit(0);
}
