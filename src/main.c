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
#include "get.h"
#include "url.h"
#include "util.h"

int main(int argc, char *argv[])
{
    int flag;

    if (argc > 2) {
        optind = 2;
        while ((flag = getopt(argc, argv, "vh:d:f:")) != -1) {
            switch (flag) {
                case 'v':
                    set_verbose();
                    set_v_verbose();
                    break;
                case 'h':
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
            struct http_url http_data = *http_parse_url(argv[optind]);
            establish_connection(&http_data, &sock);
            struct get_request* get_r = malloc(sizeof(struct get_request));
            get_r->url = http_data;
            struct http_response* res = malloc(sizeof(struct http_response));
            char *data = http_get(&sock, get_r, res);
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
