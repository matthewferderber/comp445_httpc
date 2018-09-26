//
// Created by Matthew Ferderber
// COMP445 Assignment #1
//

#ifndef A1_40010150_RESPONSE_H
#define A1_40010150_RESPONSE_H

#include "url.h"
#include "types.h"

struct http_response parse_response(struct http_response *res, char* raw_res);

#endif //A1_40010150_RESPONSE_H
