//
// Created by Matthew Ferderber
// COMP445 Assignment #1
//

#ifndef A1_40010150_HEADER_H
#define A1_40010150_HEADER_H

#include "types.h"

HttpHeader* parse_header(char* raw_head);
void print_headers(HttpResponse* r);

#endif //A1_40010150_HEADER_H
