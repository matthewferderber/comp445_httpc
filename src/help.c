//
// Created by Matthew Ferderber
// COMP445 Assignment #3
//

#include <stdio.h>
#include <string.h>

void print_help(int argc, char* argv[]) {
    if (argc >= 3) {
        if (strcmp(argv[2], "get") == 0) {
            printf("Get executes a HTTP GET request for a given URL.\n");
            printf("Usage: httpc get [-v] [-h key:value] URL\n");
            printf("\t-v\t\tPrints the detail of the response such as a protocol, status, and headers.\n");
            printf("\t-h key:value\tAssociates headers to HTTP Request with the format 'key:value'.\n");
            return;
        } else if (strcmp(argv[2], "post") == 0) {
            printf("Post executes a HTTP POST request for a given URL with inline data or data from a file.\n");
            printf("Usage: httpc post [-v] [-h key:value] [-d inline-data] [-f file] URL\n");
            printf("\t-v\t\tPrints the detail of the response such as a protocol, status, and headers.\n");
            printf("\t-h key:value\tAssociates headers to HTTP Request with the format 'key:value'.\n");
            printf("\t-d string\tAssociates an inline data to the body HTTP POST request.\n");
            printf("\t-f file\t\tAssociates the content of a file to the body HTTP POST request.\n");
            printf("Either [-d] or [-f] can be used but not both.\n");
            return;
        }
    }

    printf("httpc is a curl-like application but supports HTTP protocol only.\n");
    printf("Usage:\n");
    printf("\thttpc command [arguments]\n");
    printf("The commands are:\n");
    printf("\tget\texecutes an HTTP GET request\n");
    printf("\tpost\texecutes an HTTP POST request\n");
    printf("\thelp\tprints this screen.\n");
}
