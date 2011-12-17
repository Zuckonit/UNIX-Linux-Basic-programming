#ifndef EE_H_INCLUDED
#define EE_H_INCLUDED

#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdarg.h>
#include <stdbool.h>
#include <unistd.h>

void Usage();
void PushToBuf(char c);
void InitArgs(int argc, char *argv[]);
void EmptyBuf();
void PrintBuf();
bool CheckStr(char *mother, char *son);


#endif // EE_H_INCLUDED
