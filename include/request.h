//
// Created by Matthew Ferderber
// COMP445 Assignment #3
//

#ifndef A3_40010150_REQUEST_H
#define A3_40010150_REQUEST_H

#include "url.h"

int establish_connection(HttpUrl* http_data, int* sockfd);
void send_request(int sockfd, HttpRequest* r);
void http_request_destroy(HttpRequest* r);

#endif //A3_40010150_REQUEST_H
