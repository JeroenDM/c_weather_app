#ifndef _lib_h_
#define _lib_h_

#include <string.h>
#include <stdio.h>
#include <assert.h>

#include "utility/str_lib.h"

struct UrlData {
    double latitude;
    double longitude;
    char field_name[32];
};

struct UrlData url_data_new(double latitude, double longitude, char field_name[]);

struct String build_url(const struct UrlData url_data);

#endif
