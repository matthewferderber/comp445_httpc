//
// Created by Matthew Ferderber
// COMP445 Assignment #1
//

#ifndef A1_40010150_POST_H
#define A1_40010150_POST_H

#include "types.h"

char* http_headers_str(struct http_header* h, int num_headers);
void http_post(struct post_request* req, int* sockfd);

#endif //A1_40010150_POST_H
