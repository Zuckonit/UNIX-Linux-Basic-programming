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
/*#include <polarssl/xtea.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <wchar.h>
typedef unsigned char uchar;

int main()
{
    xtea_context xc;
    uchar key[16] = "password";

    uchar in[8] = "蚊子456", out[8];
    xtea_setup(&xc, key);

    xtea_crypt_ecb(&xc, 1, in, out);
    xtea_crypt_ecb(&xc, 0, out, in);
    write(0, in, 8);
    return 0 ;
}
*/
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
#include <stdlib.h>

typedef unsigned char uchar;

void xtea(unsigned int rounds, uint32_t in, uint32_t out, const uchar *const key, int mod)
{
	uint32_t keys[4];
	unsigned int len;
	char *pkey = (char *)malloc(sizeof(uint32_t)*4);

	  if(strlen(key) > 128)
	{
		fputs("The key is too long!\n", stderr);
		return;
	}
	if(mod != 0 && mod != 1)
	{
		fputs("Unknow mod!\n", stderr);
		return;
	}
//  	len = strlen(key);
//	strncpy(pkey, key, len);
//	while(len++ < 128) pkey[len-1] = '\0';
//	memmove(keys, pkey, 4);
	keys[0] = 98U;
	keys[1] = 97U;
	keys[2] = 98U;
	keys[3] = 6U;

	if(mod)
	{
        	unsigned int i;
        	uint32_t v0=in, v1=out, sum=0, delta=0x9E3779B9;
        	for (i=0; i < rounds; i++)
        	{
            		v0 += (((v1 << 4) ^ (v1 >> 5)) + v1) ^ (sum + keys[sum & 3]);
            		sum += delta;
            		v1 += (((v0 << 4) ^ (v0 >> 5)) + v0) ^ (sum + keys[(sum>>11) & 3]);
        	}
        	in=v0; out=v1;
	}
	else
	{
	        unsigned int i;
        	uint32_t v0=in, v1=out, delta=0x9E3779B9, sum=delta*rounds;
	        for (i=0; i < rounds; i++)
        	{
	            	v1 -= (((v0 << 4) ^ (v0 >> 5)) + v0) ^ (sum + keys[(sum>>11) & 3]);
        	    	sum -= delta;
	        	v0 -= (((v1 << 4) ^ (v1 >> 5)) + v1) ^ (sum + keys[sum & 3]);
       	 	}	
        	in=v0; out=v1;
	}
}

int main()
{
    uint32_t in = 9;
    uint32_t out = 0;
    uchar password[] = "password";
    xtea(4, in, out, password, 1);
    printf("%u\n", out);
    xtea(4, out, in, password, 0);
    printf("%u\n", in);
    
    return 0;
}

