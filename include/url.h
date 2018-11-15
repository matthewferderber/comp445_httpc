//
// Created by Matthew Ferderber
// COMP445 Assignment #3
//

#ifndef A3_40010150_URL_H
#define A3_40010150_URL_H

#include "types.h"

HttpUrl* http_parse_url(char* url);
char* protocol_str(HttpProtocol p);
void http_url_destroy(HttpUrl* url);

#endif //A3_40010150_URL_H
