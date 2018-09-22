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

#define MAXDATASIZE 1000// max number of bytes we can get at once

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

int establish_connection(struct http_url* http_data, int* sockfd) {

    // declare addrinfo structs
    struct addrinfo hints, *addr, *p;
    int status, numbytes;
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

void get_data(struct http_url* http_data, int* sockfd) {
    char buf[MAXDATASIZE];
    char msg[MAXDATASIZE];
    sprintf(msg, "GET %s HTTP/1.1\r\nHost: %s\r\nUser-Agent: httpc\r\n\r\n", http_data->path, http_data->host);
    ssize_t bytes_sent, numbytes;
    size_t len = strlen(msg);
    verbose("--Request--\n%s\n", msg);
    verbose(("sending -- "));
    if ((bytes_sent = send(*sockfd, msg, len, 0)) == -1) {
        perror("send");
        exit(1);
    }

    verbose("bytes %d\n", bytes_sent);

    if ((numbytes = recv(*sockfd, buf, MAXDATASIZE-1, 0)) == -1) {
        perror("recv");
        exit(1);
    }
    verbose("recving -- bytes %d\n", numbytes);
    printf("--Response--\n");
    printf("%s\n", (char *) buf);
}
