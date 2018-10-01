//
// Created by Matthew Ferderber
// COMP445 Assignment #1
//

#ifndef A1_40010150_RESPONSE_H
#define A1_40010150_RESPONSE_H

#include "url.h"
#include "types.h"

HttpResponse* read_response(int *sockfd);
void parse_response(HttpResponse** res, char* raw_status, char* raw_header, char* raw_body);

#endif //A1_40010150_RESPONSE_H
