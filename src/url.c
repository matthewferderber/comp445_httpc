//
// Created by Matthew Ferderber
// COMP445 Assignment #1
//

#include <stdbool.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "url.h"

void set_default_port(struct http_url* url_data) {
    url_data->port = "80";
}

void set_default_path(struct http_url* url_data) {
    url_data->path = "/";
}


// parses url into http_url struct
struct http_url* http_parse_url(const char* url) {
    struct http_url* url_data;
    url_data = malloc(sizeof(struct http_url));
    int i;
    int len = strlen(url);
    bool has_port = false;
    for(i = 0; i < len; i++) {
        if (url[i] == ':') {
            url_data->host = malloc(sizeof(char) * i);
            memcpy(url_data->host, url, i);
            has_port = true;
        } else if (url[i] == '/') {
            if (has_port) {
                int host_len = strlen(url_data->host) + 1;
                int port_len = i - host_len; 
                url_data->port = malloc(sizeof(char) * port_len);
                memcpy(url_data->port, url + host_len, port_len);
            } else {
                set_default_port(url_data);
                url_data->host = malloc(sizeof(char) * i);
                memcpy(url_data->host, url, i);
            }
            url_data->path = malloc(sizeof(char) * (len - i));
            memcpy(url_data->path, url + i, len - i);
            // path is set, skip the rest of the string
            break;
        }
    }
    
    // if the whole string was traversed, no path was found.
    if (i == len) {
        if (has_port) {
            int port_ind = strlen(url_data->host) + 1;
            url_data->port = malloc(sizeof(char) * (i - port_ind));
            memcpy(url_data->port, url + port_ind, i - port_ind);
        } else {
            set_default_port(url_data);
            url_data->host = strdup(url);
        }
        set_default_path(url_data);
    }

    printf("host: %s, port: %s, path: %s\n", url_data->host, url_data->port, url_data->path);
    return url_data;
}
