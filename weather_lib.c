#include <stdio.h>
#include <stdlib.h>

#include "weather_lib.h"

struct UrlData url_data_new(double latitude, double longitude, char field_name[])
{
    // TODO better error reporting?
    if (strlen(field_name) >= 32) {
        printf("Field name '%s' longer than %d characters.\n", field_name, 31);
        exit(1);
    }
    struct UrlData data;
	data.latitude = latitude;
	data.longitude = longitude;
	strcpy(data.field_name, field_name);
    return data;
}

struct String build_url(const struct UrlData url_data)
{
    static const char base_url[] = "https://api.open-meteo.com/v1/";
    return str_format(
        "%sforecast?latitude=%.4f&longitude=%.4f&hourly=%s_2m",
        base_url,
        url_data.latitude,
        url_data.longitude,
        url_data.field_name
    );
}
