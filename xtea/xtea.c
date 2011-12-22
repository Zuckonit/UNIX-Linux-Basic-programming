/*
 * =====================================================================================
 *
 *       Filename:  xtea.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2011年12月22日 08时12分23秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Yucoat (), thlgood(AT)yucoat.com
 *        Company:  HNUST
 *
 * =====================================================================================
 */
#include <stdio.h>
#include <stdint.h>
#include <string.h>

typedef bool 		char;
typedef unsigned char 	uchar;

void xtea(unsigned int rounds, uint32_t in, uint32_t out, const char *const key, bool mod)
{
	uchar keys[4];

	if(strlen(key) > 128)
	{
		fputs("The key is too long!\n", stderr);
		return;
	}
	if(mod != 0||mod != 1)
	{
		fputs("Unknow mod!\n", stderr);
		return;
	}
}
