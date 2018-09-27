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
#include "get.h"
#include "util.h"
#include "response.h"

#define MAXDATASIZE 512// max number of bytes we can get at once

// struct http_response http_get(struct http_url* http_data, int* sockfd) {
char *http_get(int* sockfd, struct get_request *req, struct http_response* res) {
    // allocate base buffer
    char *buf = malloc(sizeof(char) * MAXDATASIZE);
    // TODO: allow dynamic request size (find request length and then alloc the string)
    char msg[MAXDATASIZE];
    sprintf(msg, "GET %s HTTP/1.0\r\nHost: %s\r\nUser-Agent: httpc\r\n\r\n", req->url.path, req->url.host);
    size_t bytes_sent, len;
    len = strlen(msg);
    verbose("--Request--\n%s", msg);
    v_verbose(("Sending ("));
    if ((bytes_sent = send(*sockfd, msg, len, 0)) == -1) {
        perror("send");
        exit(1);
    }
    v_verbose("bytes: %zu)\n", bytes_sent);

    read_response(sockfd);
    return buf;
}
