//
// Created by Matthew Ferderber
// COMP445 Assignment #1
//

#include <stdbool.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "util.h"
#include "url.h"

void set_default_port(HttpUrl* url_data) {
    url_data->port = "80";
}

void set_default_path(HttpUrl* url_data) {
    url_data->path = "/";
}

// parses url into http_url struct
HttpUrl* http_parse_url(char* full_url) {
    HttpUrl* url_data;
    url_data = malloc(sizeof(HttpUrl));
    int i;
    int len = strlen(full_url);
    bool has_port = false;
    char* url = strstr(full_url, "://");
    if (url != NULL) {
        if (strncmp(full_url, "http", 4)) {
            if (full_url[4] == 's') {
                url_data->protocol = HTTPS;
            } else {
                url_data->protocol = HTTP;
            }
        }
        url = url + 3;
    } else {
        url = full_url;
    }

    for(i = 0; i < len; i++) {
        if (url[i] == ':') {
            url_data->host = malloc(sizeof(char) * i + 1);
            memcpy(url_data->host, url, i);
            url_data->host[i] = '\0';
            has_port = true;
        } else if (url[i] == '/') {
            if (has_port) {
                int host_len = strlen(url_data->host) + 1;
                int port_len = i - host_len; 
                url_data->port = malloc(sizeof(char) * port_len + 1);
                memcpy(url_data->port, url + host_len, port_len);
                url_data->port[i] = '\0';
            } else {
                set_default_port(url_data);
                url_data->host = malloc(sizeof(char) * i + 1);
                memcpy(url_data->host, url, i);
                url_data->host[i] = '\0';
            }
            url_data->path = malloc(sizeof(char) * (len - i) + 1);
            memcpy(url_data->path, url + i, len - i);
            url_data->path[len - i] = '\0';
            // path is set, skip the rest of the string
            break;
        }
    }

    // if the whole string was traversed, no path was found.
    if (i == len) {
        if (has_port) {
            int port_ind = strlen(url_data->host) + 1;
            url_data->port = malloc(sizeof(char) * (i - port_ind) + 1);
            memcpy(url_data->port, url + port_ind, i - port_ind);
            url_data->port[i] = '\0';
        } else {
            set_default_port(url_data);
            url_data->host = strdup(url);
        }
        set_default_path(url_data);
    }

    verbose("host: %s, port: %s, path: %s\n\0", url_data->host, url_data->port, url_data->path);
    return url_data;
}
