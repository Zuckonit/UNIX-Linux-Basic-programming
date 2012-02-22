#include <curl/curl.h>
#include <stdio.h>

int main(void)
{
	CURL *handle = NULL;
	CURLcode res;

	handle = curl_easy_init();
	if(handle != NULL)
	{
		curl_easy_setopt(handle, CURLOPT_URL, "www.yucoat.com");
		res = curl_easy_perform(handle);

		curl_easy_cleanup(handle);
	}
	return 0;
}
