//
// Created by Matthew Ferderber
// COMP445 Assignment #1
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
#include "request.h"
#include "header.h"
#include "get.h"
#include "url.h"
#include "util.h"

HttpHeader* collect_header(char* opt) {
    
}

int main(int argc, char *argv[])
{
    int flag;
    int num_headers = 0;
    HttpHeader* headers = malloc(sizeof(HttpHeader));
    HttpQueryParameter* params = malloc(sizeof(HttpQueryParameter));
    HttpHeader* h;

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
                    // realloc headers
                    // call http_header_new
                    // add returned header to last spot in headers
                    
                    //set header flag
                    break;
                case 'd':
                    //set data flag
                    break;
                case 'f':
                    //set file flag
                    //ensure d and f are not both specified
                    break;
            }
        }
        if (strcmp(argv[1], "get") == 0) {
            int sock;
            HttpUrl* url = http_parse_url(argv[optind]);
            establish_connection(url, &sock);
            GetRequest* get_r = malloc(sizeof(HttpResponse));
            get_r->http_headers = headers;
            get_r->num_headers = num_headers;
            get_r->url = url;
            HttpResponse* res = malloc(sizeof(HttpResponse));
            HttpResponse* r = http_get(&sock, get_r, res);
            printf("%s", r->raw_body);
        } else if (strcmp(argv[1], "post") == 0) {
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
