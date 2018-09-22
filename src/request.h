//
// Created by Matthew Ferderber
// COMP445 Assignment #1
//

#ifndef A1_40010150_REQUEST_H
#define A1_40010150_REQUEST_H

#include "url.h"

int establish_connection(struct http_url* http_data, int* sockfd);
void get_data(struct http_url* http_data, int* sockfd);

#endif //A1_40010150_REQUEST_H
