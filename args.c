#include <stdio.h>
#include <unistd.h>
#include <getopt.h>

int main(int argc, char *argv[])
{
	const struct option long_options[]={
		{"help", 0, NULL, 'h'},
		{"output", 1, NULL, 'o'},
		{"verbose", 0, NULL, 'v'},
		{NULL, 0, NULL, 0}
	};
	const char *const short_options = "ho:v";
	int next_option;


	while ((next_option 
			= getopt_long(argc, argv, short_options, long_options, NULL))
			!= -1)
	{
		putchar(next_option);
		putchar('\n');
	}
	return 0;
}
