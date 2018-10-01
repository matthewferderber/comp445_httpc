//
// Created by Matthew Ferderber
// COMP445 Assignment #1
//

#ifndef A1_40010150_GET_H
#define A1_40010150_GET_H

#include "request.h"
#include "types.h"

HttpResponse* http_get(int* sockfd, GetRequest *req, HttpResponse* res);
HttpResponse get_data(HttpUrl* http_data, int* sockfd);

#endif //A1_40010150_GET_H
