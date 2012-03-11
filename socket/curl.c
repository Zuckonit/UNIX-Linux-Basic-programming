#include <curl/curl.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
	int x = 10000;
	CURL *cu;
	cu = curl_easy_init();
	curl_easy_setopt(cu, CURLOPT_URL, argv[1]);

	while (x--)
		curl_easy_perform(cu);
	curl_easy_cleanup(cu);
	
	return 0;
}
