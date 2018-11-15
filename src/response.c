//
// Created by Matthew Ferderber
// COMP445 Assignment #3
//

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <unistd.h>

#include "response.h"
#include "header.h"
#include "util.h"
#include "url.h"
#include "types.h"

// returns number of headers parsed into header param
// TODO: clean up this function
// TODO: Seperate per-header parsing into new function in header.c (used for req and res)
int parse_headers(HttpHeader** headers, char* raw_header) {
    int num_headers = 0;
    int i;
    int next_start = 0;
    for (i = 0; raw_header[i] != '\0'; i++) {
        if (raw_header[i] == '\r' && raw_header[i + 1] == '\n') {
            if (raw_header[i + 2] != '\0') {
                char* h = malloc(sizeof(char) * (i - next_start + 1));
                memcpy(h, raw_header + next_start, i - next_start);
                h[i - next_start] = '\0';

                num_headers++;
                if (num_headers > 1) {
                    *headers = realloc(*headers, sizeof(HttpHeader) * num_headers);
                }
                (*headers)[num_headers - 1] = *parse_header(h);
                free(h);
                next_start = i + 2;
            }
        }
    }
    return num_headers;
}

void parse_response(HttpResponse* res, char* raw_status, char* raw_header, char* raw_body) {
    HttpHeader* header = malloc(sizeof(HttpHeader));
    int num_headers = parse_headers(&header, raw_header);
    v_verbose("%d headers parsed from response\n", num_headers);
    res->http_headers = header;
    res->num_headers = num_headers;
    res->raw_body = raw_body;
    res->http_status = "200";
}

HttpResponse* read_response(int sockfd) {
    char* buf = malloc(sizeof(char) * MAXDATASIZE);
    char* start_of_header = NULL;
    char* end_of_header = NULL;
    char* raw_header = NULL;
    char* raw_status = NULL;
    char* raw_body = NULL;
    size_t numbytes, chunk, content_length, header_length, status_length, total_bytes;
    header_length = 0;
    total_bytes = 0;
    chunk = 0;
    int i = 1;
    int num_reallocs = 0;
    _Bool found_content_length = false;
    _Bool found_header_length = false;
    // recv until numbytes is 0 or less (connection close or error)
    while ((numbytes = recv(sockfd, buf + total_bytes, MAXDATASIZE-1, 0)) > 0) {
        i++;
        total_bytes += numbytes;
        chunk += numbytes;
        // Add temp null terminator for str functions
        buf[total_bytes] = '\0';

        // If content_length hasn't been found
        if (!found_content_length) {
            char* len_header= strstr(buf, "Content-Length: ");
            if (len_header != NULL) {
                found_content_length = true;
                len_header += 16;
                char *afterHeader;

                content_length = strtol(len_header, &afterHeader, 10);
                v_verbose("Found Content-Length: %zu\n", content_length);
            }
        }

        if (start_of_header == NULL) {
            start_of_header = strstr(buf, "\r\n") + 2;
            if (start_of_header != NULL) {
                //TODO: change this to use memcpy
                status_length = char_distance(start_of_header, buf);
                raw_status = strndup(buf, char_distance(start_of_header - 2, buf));
            }
        }

        if (!found_header_length) {
            end_of_header = strstr(buf, "\r\n\r\n");
            if (end_of_header != NULL) {
                found_header_length = true;
                header_length = char_distance(end_of_header, start_of_header);
                raw_header = malloc(sizeof(char) * (header_length + 1));
                memcpy(raw_header, start_of_header, header_length);
                raw_header[header_length] = '\0';
            }
            v_verbose("Header Size: %zu\n", header_length);
        }

        // if content_length exists and the body has been received, exit recv
        if (found_content_length && (total_bytes - (header_length + status_length + 4)) == content_length) {
            v_verbose("Content-Length reached, closing recv\n");
            break;
        }

        if (chunk >= MAXDATASIZE - 1) {
            buf = realloc(buf, sizeof(char) * (total_bytes + (MAXDATASIZE * 2)));
            if (buf == NULL) {
                printf("out of memory");
                exit(1);
            }
            num_reallocs++;
            chunk = 0;
        }
    }
    if (numbytes == -1) {
        perror("recv");
        exit(1);
    }
    // null terminate end of buffer
    buf[total_bytes] = '\0';
    //raw_body is buf without status and header (and new-lines)
    int body_size = total_bytes - header_length - status_length - 4;
    raw_body = malloc(sizeof(char) * (body_size + 1));
    memcpy(raw_body, buf + header_length + status_length + 4, body_size);
    raw_body[body_size] = '\0';
    free(buf);

    v_verbose("# of recvs: %d\n# of reallocs: %d\n", i, num_reallocs);
    // if header isn't set, there was no double escape therefore, no body
    if (raw_header == NULL) {
        raw_header = start_of_header;
        raw_body = NULL;
    }
    verbose("Total bytes: %d\n", total_bytes);
    HttpResponse* res = malloc(sizeof(HttpResponse) * 1);
    parse_response(res, raw_status, raw_header, raw_body);
    free(raw_header);
    free(raw_status);
    return res;
}

void http_response_destroy(HttpResponse* r) {
    int i;
    for(i = 0; i < r->num_headers; i++) {
        http_header_destroy(&(r->http_headers[i]));
    }
    free(r->raw_body);
    //free(r->http_status);
    free(r);
    r = NULL;
}
