//
// Created by Matthew Ferderber
// COMP445 Assignment #1
//

#ifndef A1_40010150_TYPES_H
#define A1_40010150_TYPES_H

enum http_protocol { HTTP, HTTPS };

struct http_url {
    enum http_protocol protocol;
    char* host;
    char* port;
    char* path;
};

struct http_header {
    char* key;
    char* value;
};

struct http_response {
    struct http_header* http_headers;
    char* raw_body;
    char* http_status;
};

struct http_query_parameter {
    char* key;
    char* value;
};

struct get_request {
    struct http_url url;
    struct http_header* http_headers;
    struct http_query_parameter* query_parameters;
};

struct post_request {
    struct http_url url;
    struct http_header* http_headers;
    char* raw_body;
};

#endif //A1_40010150_TYPES_H
