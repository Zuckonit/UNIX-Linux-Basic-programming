#include <stdio.h>
#include <stdlib.h>
#include <curl/curl.h>

static size_t write_func(char *src, size_t size, size_t n, void *stream)
{
	fwrite(src, size, n, (FILE *)stream);
	return n;
}

int main(int argc, char *argv[])
{
	CURL *cuHand;
	FILE *data;
	FILE *head;

	if ((head = fopen("head.txt", "w")) == NULL)
	{
		perror("fopen_head");
		exit(1);
	}
	if((data = fopen("/dev/null", "w")) == NULL)
	{
		perror("fopen_data");
		exit(1);
	}

	cuHand = curl_easy_init();
	curl_easy_setopt(cuHand, CURLOPT_URL, argv[1]);
	curl_easy_setopt(cuHand, CURLOPT_WRITEFUNCTION, write_func);
	curl_easy_setopt(cuHand, CURLOPT_NOPROGRESS, 1L);
	curl_easy_setopt(cuHand, CURLOPT_WRITEDATA, data);
	curl_easy_setopt(cuHand, CURLOPT_WRITEHEADER, stdout);

	curl_easy_perform(cuHand);

	curl_easy_cleanup(cuHand);
	fclose(data);
	fclose(head);
	exit (0);
}
