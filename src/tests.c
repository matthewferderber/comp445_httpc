//
// Created by Matthew Ferderber
// COMP445 Assignment #1
//

#include <stdio.h>
#include "types.h"
#include "request.h"
#include "response.h"

void post_example() {
    printf("\n\n---- POST httpbin.org/post\n");

    int sock;
    HttpRequest r = {};
    HttpUrl url = {};
    url.host = "httpbin.org";
    url.port = "80";
    url.path = "/post";
    establish_connection(&url, &sock);
    r.url = &url;
    r.num_headers = 1;
    r.num_params = 0;
    HttpHeader headers[1];
    headers[0].key = "Connection";
    headers[0].value = "close";
    r.http_headers = headers;
    r.method = "POST";
    r.raw_body = "Sample POST request body";
    send_request(sock, &r);
    HttpResponse* res = read_response(sock);
    printf("%s", res->raw_body);
    http_response_destroy(res);

}
void get_example() {
    printf("\n\n---- GET httpbin.org/status/418\n");

    int sock;
    HttpRequest r = {};
    HttpUrl url = {};
    url.host = "httpbin.org";
    url.port = "80";
    url.path = "/status/418";
    establish_connection(&url, &sock);
    r.url = &url;
    r.num_headers = 1;
    r.num_params = 0;
    HttpHeader headers[1];
    headers[0].key = "Connection";
    headers[0].value = "close";
    r.http_headers = headers;
    r.method = "GET";
    r.raw_body = NULL;
    send_request(sock, &r);
    HttpResponse* res = read_response(sock);
    printf("%s", res->raw_body);
    http_response_destroy(res);

    printf("\n\n---- GET httpbin.org/status/418\n");
    url.path = "/get?query_parameter=hello";
    establish_connection(&url, &sock);
    r.url = &url;
    r.method = "GET";
    send_request(sock, &r);
    res = read_response(sock);
    printf("%s", res->raw_body);
    http_response_destroy(res);
}


int main() {
    printf("---- Running httpc tests\n");
    get_example();
    post_example();
}

