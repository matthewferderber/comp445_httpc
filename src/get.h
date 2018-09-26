//
// Created by Matthew Ferderber
// COMP445 Assignment #1
//

#ifndef A1_40010150_GET_H
#define A1_40010150_GET_H

#include "request.h"
#include "types.h"

char *http_get(int* sockfd, struct get_request *req, struct http_response* res);
struct http_response get_data(struct http_url* http_data, int* sockfd);

#endif //A1_40010150_GET_H
