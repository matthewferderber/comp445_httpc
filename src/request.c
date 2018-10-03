//
// Created by Matthew Ferderber
// COMP445 Assignment #1
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <unistd.h>

#include "util.h"
#include "request.h"
#include "types.h"


// get addr from sockaddr, (either ipv4 or ipv6):
void *get_addr(struct sockaddr *s_addr)
{
    // if address is ipv4, return in_addr
    if (s_addr->sa_family == AF_INET) {
        return &(((struct sockaddr_in*)s_addr)->sin_addr);
    }

    // return in6_addr
    return &(((struct sockaddr_in6*)s_addr)->sin6_addr);
}

int establish_connection(HttpUrl* http_data, int* sockfd) {

    // declare addrinfo structs
    struct addrinfo hints, *addr, *p;
    int status;
    char s[INET6_ADDRSTRLEN];


    memset(&hints, 0, sizeof hints);
    // fill hints (so getaddrinfo knows what to look for)
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;

    // retrieve address information for domain
    if ((status = getaddrinfo(http_data->host, http_data->port, &hints, &addr)) != 0) {
        fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(status));
        return 2;
    }

    // connect to the first possible address
    for(p = addr; p != NULL; p = p->ai_next) {
        if ((*sockfd = socket(p->ai_family, p->ai_socktype,
                             p->ai_protocol)) == -1) {
            perror("Client: socket");
            continue;
        }

        if (connect(*sockfd, p->ai_addr, p->ai_addrlen) == -1) {
            close(*sockfd);
            perror("Client: connect");
            continue;
        }
        break;
    }
    if (p == NULL) {
        fprintf(stderr, "Client: unable to connect to host\n");
        return 2;
    }

    // get human readable string address
    inet_ntop(p->ai_family, get_addr(p->ai_addr), s, sizeof s);
    verbose("Client: connecting to %s\n", s);

    freeaddrinfo(addr); // frees dynamic memory allocated for addr
    return 0;
}

char* construct_query_string(HttpQueryParameter* params, int num_params) {
    char* buf = malloc(sizeof(char) * MAXDATASIZE);
    size_t len = 0;
    size_t k_size = 0;
    size_t v_size = 0;
    size_t chunk = 0;
    int i;
    for(i = 0; i < num_params; i++) {
        k_size = strlen(params[i].key);
        v_size = strlen(params[i].value);
        chunk += k_size + v_size + 2;
        if (chunk > MAXDATASIZE) {
            buf = realloc(buf, sizeof(char) * (MAXDATASIZE + len));
            chunk = 0;
        }
        memcpy(buf + len, params[i].key, k_size);
        // if first param, use ? not &
        buf[len] = i == 0 ? '?' : '&';
        len += k_size + 2;
        buf[len + 1] = '=';
        memcpy(buf + len, params[i].value, v_size);
    }
    buf[len] = '\0';
    return buf;
}

char* construct_header_str(HttpHeader* headers, int num_headers) {
    char* buf = malloc(sizeof(char) * MAXDATASIZE);
    size_t len = 0;
    size_t k_size = 0;
    size_t v_size = 0;
    size_t chunk = 0;
    int i;
    for(i = 0; i < num_headers; i++) {
        k_size = strlen(headers[i].key);
        v_size = strlen(headers[i].value);
        chunk += k_size + v_size + 4;
        if (chunk > MAXDATASIZE) {
            buf = realloc(buf, sizeof(char) * (MAXDATASIZE + len + 1));
            chunk = 0;
        }
        memcpy(buf + len, headers[i].key, k_size);
        buf[len + k_size] = ':';
        buf[len + k_size + 1] = ' ';
        len += k_size + 2;
        memcpy(buf + len, headers[i].value, v_size);
        buf[len + v_size] = '\r';
        buf[len + v_size + 1] = '\n';
        len += v_size + 2;
    }
    buf[len] = '\0';
    return buf;
}

char* construct_url(HttpUrl* url, HttpQueryParameter* params, int num_params) {
    //char* buf = construct_query_string(params, num_params);
    char* full_url = malloc(sizeof(char) * MAXDATASIZE);
    sprintf(full_url, "%s://%s", protocol_str(url->protocol), url->host);
    return full_url;
}

void send_request(int sockfd, HttpRequest* r) {
    //char* url = construct_url(r->url, r->query_parameters, r->num_params);
    char* headers = construct_header_str(r->http_headers, r->num_headers);
    char* msg = malloc(sizeof(char) * MAXDATASIZE);
    size_t len;
    if (r->raw_body != NULL) {
        size_t body_len = strlen(r->raw_body);
        len = sprintf(msg, "%s %s HTTP/1.1\r\nHost: %s\r\nContent-Length: %zu\r\n%s\r\n%s", r->method, r->url->path, r->url->host, body_len, headers, r->raw_body);
    } else {
        len = sprintf(msg, "%s %s HTTP/1.1\r\nHost: %s\r\n%s\r\n", r->method, r->url->path, r->url->host, headers);
    }
    size_t bytes_sent;
    verbose("--Request--\n%s--Request--\n", msg);
    v_verbose("Sending");
    if ((bytes_sent = send(sockfd, msg, len, 0)) == -1) {
        perror("send");
        exit(1);
    }
    v_verbose("(bytes: %zu)\n", bytes_sent);
}
