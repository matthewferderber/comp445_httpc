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

#include "post.h"
#include "util.h"

#define MAXDATASIZE 1000// max number of bytes we can get at once

// returns number of characters written
int write_str(char* str, char* str2) {
    int n = 0;
    for(n = 0; str2[n] != '\0'; n++) {
        str[n] = str2[n];
    }
    return n;
}

char* http_headers_str(HttpHeader* h, int num_headers) {
    int i, total = 0;
    char* header_s = NULL;
    for(i = 0; i < num_headers; i++) {
        int s1_len = strlen(h[i].key);
        int s2_len = strlen(h[i].value);
        total += s1_len + s2_len + 4;
        header_s = realloc(header_s, sizeof(char) * (total));
        strcat(header_s, h[i].key);
        strcat(header_s, ": ");
        strcat(header_s, h[i].value);
        strcat(header_s, "\r\n");
    }
    printf("total size: %lu, total alloc: %d\n", strlen(header_s), total);
    printf("%s\n", header_s);
    return header_s;
}

void http_post(PostRequest* req, int* sockfd) {
    char buf[MAXDATASIZE];
    char msg[MAXDATASIZE];
    sprintf(msg, "POST %s HTTP/1.1\r\nHost: %s\r\nUser-Agent: httpc\r\n\r\n", req->url.path, req->url.host);
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
    //null terminate end of used buffer
    buf[numbytes] = '\0';
    printf("%s\n", (char *) buf);
}

