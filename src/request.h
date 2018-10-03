//
// Created by Matthew Ferderber
// COMP445 Assignment #1
//

#ifndef A1_40010150_REQUEST_H
#define A1_40010150_REQUEST_H

#include "url.h"

int establish_connection(HttpUrl* http_data, int* sockfd);
void send_request(int sockfd, HttpRequest* r);
void http_request_destroy(HttpRequest* r);

#endif //A1_40010150_REQUEST_H
