#include <assert.h>
#include <string.h>

#include "lib.h"

void test_url_builder()
{
	const char expected[] = "https://api.open-meteo.com/v1/\
forecast?latitude=38.5737&longitude=-121.4871&hourly=temperature_2m";

	struct UrlData data;
	data.latitude = 38.5737;
	data.longitude = -121.4871;
	strcpy(data.field_name, "temperature");

	char buffer[100];
	build_url(data, buffer);
	printf("%s\n", buffer);

	assert(strcmp(buffer, expected) == 0);
}

int main()
{
	test_url_builder();
}
