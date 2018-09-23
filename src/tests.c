//
// Created by Matthew Ferderber
// COMP445 Assignment #1
//

#include <stdio.h>
#include "post.h"
#include "types.h"

int main() {
    printf("Running httpc tests\n");

    struct post_request r = {};
    struct http_url url = {};
    url.host = "google.ca";
    url.port = "80";
    url.path = "/";
    r.url = url;
    struct http_header headers[1];
    headers[0].key = "Key";
    headers[0].value = "Value";
    r.http_headers = headers;

    char* headers_str = http_headers_str(headers, 1);
    printf("%s\n", headers_str);
}
