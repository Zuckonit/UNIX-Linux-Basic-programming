#include "ee.h"

extern char *LineBuf;
extern int  BufLen;

void PushToBuf(char c)
{
	LineBuf = realloc(LineBuf, (BufLen+2)*sizeof(char));
	LineBuf[BufLen] = c;
	BufLen++;
	LineBuf[BufLen] = '\0';
}

void EmptyBuf()
{
	free(LineBuf);
	LineBuf = NULL;
	BufLen = 0;
}

void PrintBuf()
{
	char *p = LineBuf;
	while (*p != '\0')
	{
		putchar(*p);
		p++;
	}
}

bool CheckStr(char *mother, char *son)
{
	if (mother == NULL)
		return false;
	int MatchSize = 0;
	char *p = mother;

	while (*p != '\0' && son[MatchSize] != '\0')
	{
		if (*p == son[MatchSize])
			MatchSize++, p++;
		else
			MatchSize = 0, p++;
	}
	return (MatchSize == strlen(son))?true:false;
}
