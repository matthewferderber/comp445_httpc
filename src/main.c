//
// Created by Matthew Ferderber
// COMP445 Assignment #3
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <string.h>
#include <getopt.h>

#include "help.h"
#include "types.h"
#include "request.h"
#include "response.h"
#include "header.h"
#include "url.h"
#include "util.h"
#include "file_reader.h"

int main(int argc, char *argv[])
{
    int flag;
    int num_headers = 0;
    HttpHeader* headers = malloc(sizeof(HttpHeader));
    HttpHeader* h;
    char* raw_body = NULL;
    int len;

    if (argc > 2) {
        optind = 2;
        while ((flag = getopt(argc, argv, "vh:d:f:")) != -1) {
            switch (flag) {
                case 'v':
                    set_verbose();
                    set_v_verbose();
                    break;
                case 'h':
                    h = parse_header(optarg);
                    num_headers++;
                    headers = realloc(headers, sizeof(HttpHeader) * num_headers);
                    headers[num_headers - 1] = *h;
                    break;
                case 'd':
                    if (raw_body != NULL) {
                        printf("Only one of -f -d can be specified at a time.\n");
                        exit(1);
                    }
                    len = strlen(optarg);
                    raw_body = malloc(sizeof(char) * (len + 1));
                    memcpy(raw_body, optarg, len);
                    raw_body[len] = '\0';
                    break;
                case 'f':
                    if (raw_body != NULL) {
                        printf("Only one of -f -d can be specified at a time.\n");
                        exit(1);
                    }
                    read_file(&raw_body, optarg);
                    break;
            }
        }
        int sock;
        if (strcmp(argv[1], "get") == 0) {
            HttpUrl* url = http_parse_url(argv[optind]);
            establish_connection(url, &sock);
            HttpRequest* req = malloc(sizeof(HttpRequest));
            req->method = "GET";
            req->http_headers = headers;
            req->num_headers = num_headers;
            req->url = url;
            req->raw_body = NULL;
            send_request(sock, req);
            http_request_destroy(req);
            HttpResponse* r = read_response(sock);
            if (is_verbose()) {
                print_headers(r->http_headers, r->num_headers);
            }
            printf("%s", r->raw_body);
            http_response_destroy(r);
        } else if (strcmp(argv[1], "post") == 0) {
            HttpUrl* url = http_parse_url(argv[optind]);
            establish_connection(url, &sock);
            HttpRequest* req = malloc(sizeof(HttpRequest));
            req->method = "POST";
            req->http_headers = headers;
            req->num_headers = num_headers;
            req->url = url;
            req->raw_body = raw_body;
            send_request(sock, req);
            http_request_destroy(req);
            HttpResponse* r = read_response(sock);
            printf("%s", r->raw_body);
            http_response_destroy(r);
        } else if (strcmp(argv[1], "help") == 0) {
            print_help(argc, argv);
        } else {
            print_help(argc, argv);
        }

    } else {
        print_help(argc, argv);
    }
    return 0;
}
