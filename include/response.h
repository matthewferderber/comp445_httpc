//
// Created by Matthew Ferderber
// COMP445 Assignment #3
//

#ifndef A3_40010150_RESPONSE_H
#define A3_40010150_RESPONSE_H

#include "url.h"
#include "types.h"

HttpResponse* read_response(int sockfd);
void parse_response(HttpResponse* res, char* raw_status, char* raw_header, char* raw_body);
void http_response_destroy(HttpResponse* r);

#endif //A3_40010150_RESPONSE_H
