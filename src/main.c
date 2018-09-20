//
// Created by Matthew Ferderber
// COMP445 Assignment #1
//

#include <stdio.h>
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
#include "url.h"

int main(int argc, char *argv[])
{
    int flag;

    if (argc > 1) {
        if (strcmp(argv[1], "get") == 0) {
        } else if (strcmp(argv[1], "post") == 0) {
        } else if (strcmp(argv[1], "help") == 0) {
            print_help(argc, argv);
        } else {
        }
        optind = 2;
        while ((flag = getopt(argc, argv, "vh:d:f:")) != -1) {
            switch (flag) {
                case 'v':
                    //set verbose flag
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

        int sock;
        struct http_url http_data = *http_parse_url(argv[optind]);
        establish_connection(&http_data, &sock);
        get_data(&http_data, &sock);
    } else {
        print_help(argc, argv);
    }
    return 0;
}
