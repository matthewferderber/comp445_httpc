//
// Created by Matthew Ferderber
// COMP445 Assignment #1
//

#ifndef A1_40010150_TYPES_H
#define A1_40010150_TYPES_H

typedef enum http_protocol_t { HTTP, HTTPS } HttpProtocol;

typedef struct http_url_t {
    HttpProtocol protocol;
    char* host;
    char* port;
    char* path;
} HttpUrl;

typedef struct http_header_t {
    char* key;
    char* value;
} HttpHeader;

typedef struct http_response_t {
    int num_headers;
    HttpHeader* http_headers;
    char* raw_body;
    char* http_status;
} HttpResponse;

typedef struct  http_query_parameter_t {
    char* key;
    char* value;
} HttpQueryParameter;

typedef struct get_request_t {
    HttpUrl url;
    int num_headers;
    HttpHeader* http_headers;
    HttpQueryParameter* query_parameters;
} GetRequest;

typedef struct post_request_t {
    HttpUrl url;
    HttpHeader* http_headers;
    char* raw_body;
} PostRequest;

#endif //A1_40010150_TYPES_H
