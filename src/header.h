//
// Created by Matthew Ferderber
// COMP445 Assignment #1
//

#ifndef A1_40010150_HEADER_H
#define A1_40010150_HEADER_H

#include "types.h"

HttpHeader* parse_header(char* raw_head);
void print_headers(HttpHeader* h, int num_headers);
void http_header_new(HttpHeader* h, char* key, char* value);
void http_header_destroy(HttpHeader* h);

#endif //A1_40010150_HEADER_H
