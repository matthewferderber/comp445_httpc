//
// Created by Matthew Ferderber
// COMP445 Assignment #3
//

#ifndef A3_40010150_HEADER_H
#define A3_40010150_HEADER_H

#include "types.h"

HttpHeader* parse_header(char* raw_head);
void print_headers(HttpHeader* h, int num_headers);
void http_header_new(HttpHeader* h, char* key, char* value);
void http_header_destroy(HttpHeader* h);

#endif //A3_40010150_HEADER_H
