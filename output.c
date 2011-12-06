#include "thlgood.h"

int main(void)
{
	char Str[20];
	char p[20];

	FILE *fp;
	if ((fp = fopen("out", "wb")) == NULL)
	{
		perror("fopen");
		exit(-1);
	}

	/* gets()function is very dangerous! */
	gets(Str);
	Ps(Str);		//Ps() is print string!

	/* fgets()function is more safe than gets() */
	fgets(p, 19, stdin);
	printf("P=\n");
	Ps(p);

	sprintf(Str, "%s", p);
	Ps(Str);
	snprintf(Str, strlen(p) - 1, "%s", p);
	Ps(Str);

	fprintf(fp, "%s", Str);

	fclose(fp);
	return 0;
}
