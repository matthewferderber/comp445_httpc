//
// Created by Matthew Ferderber
// COMP445 Assignment #1
//

#include <stdio.h>
#include "types.h"

int main() {
    printf("Running httpc tests\n");

    HttpRequest r = {};
    HttpUrl url = {};
    url.host = "google.ca";
    url.port = "80";
    url.path = "/";
    r.url = &url;
    HttpHeader headers[1];
    headers[0].key = "Key";
    headers[0].value = "Value";
    r.http_headers = headers;
}
