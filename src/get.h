//
// Created by Matthew Ferderber
// COMP445 Assignment #1
//

#ifndef A1_40010150_GET_H
#define A1_40010150_GET_H

#include "request.h"

void http_get(int sockfd, struct get_request req, struct http_response* res);


#endif //A1_40010150_GET_H
