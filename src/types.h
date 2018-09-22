//
// Created by Matthew Ferderber
// COMP445 Assignment #1
//

#ifndef A1_40010150_TYPES_H
#define A1_40010150_TYPES_H

struct http_header {
    char* key;
    char* value;
};

struct http_response {
    struct http_header* http_headers;
    char* raw_body;
    char* http_status;
};


struct get_request {
    struct http_url url;
    struct http_header* http_headers;
    struct http_query_parameters* query_parameters;
};

struct http_url {
    char* host;
    char* port;
    char* path;
};

#endif //A1_40010150_TYPES_H
