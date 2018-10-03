//
// Created by Matthew Ferderber
// COMP445 Assignment #1
//

#ifndef A1_40010150_GET_H
#define A1_40010150_GET_H

#include "request.h"
#include "types.h"

HttpResponse* http_get(int sockfd, GetRequest *req, HttpResponse* res);
HttpResponse get_data(HttpUrl* http_data, int sockfd);
void get_request_new(GetRequest* r, HttpUrl* url, HttpHeader* headers, int num_headers, HttpQueryParameter* params);
void get_request_destroy(GetRequest* r);

#endif //A1_40010150_GET_H
