#include <curl/curl.h>
#include <stdio.h>

#define URL "https://www.alipay.com"

int main(void)
{
	CURL *curl;
	CURLcode res;

	if ((curl = curl_easy_init()) != NULL)
	{
		curl_easy_setopt(curl, CURLOPT_URL, URL);
		curl_easy_setopt(curl, CURLOPT_CAPATH, "./V.pem");
		res = curl_easy_perform(curl);
		curl_easy_cleanup(curl);
	}
	else
	{
		fputs("curl init failured!", stderr);
	}
	return 0;
}
