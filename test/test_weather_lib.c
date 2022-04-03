#include <stdio.h>
#include <string.h>

#include "weather_lib.h"

void test_url_data_new()
{
    struct UrlData d = url_data_new(32.4, 32.5, "temperature");
    assert(d.latitude == 32.4);
    assert(d.longitude == 32.5);
    assert(strcmp(d.field_name, "temperature") == 0);
}

void test_url_builder()
{
    struct String result = build_url(url_data_new(32.4, 32.5, "temp"));

    char expected[] = "https://api.open-meteo.com/v1/\
forecast?latitude=32.4000&longitude=32.5000&hourly=temp_2m";

    assert(strlen(result.c_str) == strlen(expected));
    assert(strcmp(result.c_str, expected) == 0);
}

int main()
{
    test_url_builder();
}
