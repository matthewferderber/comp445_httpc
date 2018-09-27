//
// Created by Matthew Ferderber
// COMP445 Assignment #1
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
#include "util.h"

#define MAXDATASIZE 512// max number of bytes we can get at once

// returns number of headers parsed into header param
// TODO: clean up this function
// TODO: Seperate per-header parsing into new function in header.c (used for req and res)
int parse_header(struct http_header** headers, char* raw_header) {
    int num_headers = 0;
    struct http_header* new_headers = malloc(sizeof(struct http_header) * num_headers);
    int i;
    int num_bytes = 0;
    int next_start = 0;
    for (i = 0; raw_header[i] != '\0'; i++) {
        if (raw_header[i] == '\r' && raw_header[i + 1] == '\n') {
            char *h = malloc(sizeof(char) * (i - next_start + 1));
            memcpy(h, raw_header + next_start, i - next_start);
            h[i - next_start] = '\0';
            int k;
            char *key = NULL;
            char *val;
            for (k = 0; h[k] != '\0'; k++) {
                if (h[k] == ':') {
                    free(key);
                    key = malloc(sizeof(char) * k + 1);
                    memcpy(key, h, k);
                    key[k] = '\0';
                    break;
                }
            }
            if (key != NULL) {
                val = strdup(h + k + 2);
                int key_len = k;
                size_t val_len = strlen(val);
                num_bytes += key_len + 1;
                num_bytes += val_len + 1;
                num_headers++;
                new_headers = realloc(new_headers, sizeof(new_headers) * num_headers + num_bytes);
                if (headers == NULL) {
                    printf("Out of memory\n");
                    exit(1);
                }
                new_headers[num_headers - 1].key = malloc(sizeof(char) * (key_len + 1));
                new_headers[num_headers - 1].value = malloc(sizeof(char) * (val_len + 1));
                memcpy(new_headers[num_headers - 1].key, key, key_len);
                new_headers[num_headers - 1].key[key_len] = '\0';
                memcpy(new_headers[num_headers - 1].value, val, val_len);
                new_headers[num_headers - 1].value[val_len] = '\0';
            }
            next_start = i + 2;

        }
    }
    *headers = new_headers;
    return num_headers;
}

// TODO: impl status parse and body parse
void parse_response(struct http_response* res, char* raw_status, char* raw_header, char* raw_body) {
    struct http_header* header = malloc(sizeof(struct http_header));
    int num_headers = parse_header(&header, raw_header);
    res->http_headers = header;
    res->num_headers = num_headers;
}

void read_response(int *sockfd) {
    char* buf = malloc(sizeof(char) * MAXDATASIZE);
    size_t numbytes, chunk, content_length, header_length, total_bytes;
    total_bytes = 0;
    chunk = 0;
    int i = 1;
    char* start_of_header = NULL;
    int num_reallocs = 0;
    _Bool found_content_length = false;
    _Bool found_header_length = false;
    char* raw_header;
    char* raw_status;
    // recv until numbytes is 0 or less (connection close or error)
    while ((numbytes = recv(*sockfd, buf + total_bytes, MAXDATASIZE-1, 0)) > 0) {
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
            raw_status = strndup(buf, char_distance(start_of_header - 2, buf));
        }
      }

      if (found_content_length && !found_header_length) {
        char* end_of_header = strstr(buf, "\r\n\r\n");
        if (end_of_header != NULL) {
          found_header_length = true;
          header_length = char_distance(end_of_header + 4, buf);
          raw_header = malloc(sizeof(char) * header_length);
          memcpy(raw_header, start_of_header, header_length);
        }
        v_verbose("Header Size: %zu\n", header_length);
      }

      // if content_length exists and the body has been received, exit recv
      if (found_content_length && (total_bytes - header_length) == content_length) {
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
    char* raw_body = strdup(buf + header_length);
    v_verbose("# of recvs: %d\n# of reallocs: %d\n", i, num_reallocs);
    // null terminate end of buffer
    buf[total_bytes] = '\0';
    verbose("Total bytes: %d\n", total_bytes);
    struct http_response* res = malloc(sizeof(struct http_response) * 1);
    parse_response(res, raw_status, raw_header, raw_body);
}
