#include <stdio.h>
#include <string.h>
#include <iconv.h>

int main()
{
    char input[BUFSIZ];
    char output[BUFSIZ];
    size_t insize = BUFSIZ;
    size_t outsize = BUFSIZ;

    char *inp = input;
    char *outp = output;

    iconv_t cd = iconv_open("gb2312", "utf-8");

    memset(input, '\0', sizeof(input));
    memset(output, '\0', sizeof(output));
//	freopen("input", "r", stdin);
    scanf("%s", input);
    insize = strlen(input);

    iconv(cd, &inp, &insize, &outp, &outsize);
    printf("%s\n", output);
    iconv_close(cd);
    return 0;
}
