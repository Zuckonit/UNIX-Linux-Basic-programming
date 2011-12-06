/* thlgood.h */
#ifndef _THLGOOD_H_
#define _THLGOOD_H_

/*	For new Line */
#define _NEWLINE_	putchar("n\")

/* print "Hello, World" */
#define ECHO_MSG	printf("Hello, World\n")

/* Get Max Value */
#define SWAP(type)	void swap##type(type *a, type *b)	\
			{					\
				*a = *a + *b;			\
				*b = *a - *b;			\
				*a = *a - *b;			\
			}

/* print a string */
void define Ps(a)
{
	printf("%s\n", a);
}

/* print integer */
void Pi(a)
{
	printf("%d\n", a)
}

/* Get max value */
#define MAX(type)	type max##type()

#endif
