#include <stdio.h>
#include <curl/curl.h>

// #include "utility/str_lib.h"
#include "weather_lib.h"

int main()
{
	CURL *curl;
	CURLcode res;

// 	    char url[] = "https://api.open-meteo.com/v1/\
// forecast?latitude=38.5737&longitude=-121.4871&hourly=temperature_2m";

	struct UrlData data = url_data_new(38.5737, -121.4871, "temperature");
	struct String url = build_url(data);
	printf("%s\n", url.c_str);

	FILE *fp = fopen("resp.xml", "wb");

	/* In windows, this will init the winsock stuff */
	curl_global_init(CURL_GLOBAL_ALL);

	/* get a curl handle */
	curl = curl_easy_init();
	if (curl) {
		/* First set the URL that is about to receive our POST. This URL can
            just as well be a https:// URL if that is what should receive the
            data. */
		curl_easy_setopt(curl, CURLOPT_URL, url.c_str);
		// curl_easy_setopt(curl, CURLOPT_WRITEDATA, fp);

		/* Perform the request, res will get the return code */
		res = curl_easy_perform(curl);
		puts("");
		/* Check for errors */
		if (res != CURLE_OK)
			fprintf(stderr, "curl_easy_perform() failed: %s\n",
				curl_easy_strerror(res));

		fclose(fp);

		/* always cleanup */
		curl_easy_cleanup(curl);
	}
	curl_global_cleanup();
	str_delete(&url);
	return 0;
}
