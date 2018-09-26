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

#define MAXDATASIZE 512// max number of bytes we can get at once

// struct http_response http_get(struct http_url* http_data, int* sockfd) {
char *http_get(int* sockfd, struct get_request *req, struct http_response* res) {
    // allocate base buffer
    char *buf = malloc(sizeof(char) * MAXDATASIZE);
    // TODO: allow dynamic request size (find request length and then alloc the string)
    char msg[MAXDATASIZE];
    sprintf(msg, "GET %s HTTP/1.0\r\nHost: %s\r\nUser-Agent: httpc\r\n\r\n", req->url.path, req->url.host);
    size_t bytes_sent, numbytes, chunk, content_length, header_length, total_bytes;
    size_t len = strlen(msg);
    verbose("--Request--\n%s", msg);
    v_verbose(("Sending ("));
    if ((bytes_sent = send(*sockfd, msg, len, 0)) == -1) {
        perror("send");
        exit(1);
    }
    v_verbose("bytes: %zu)\n", bytes_sent);

    total_bytes = 0;
    chunk = 0;
    int i = 1;
    int num_reallocs = 0;
    _Bool found_content_length = false;
    _Bool found_header_length = false;
    // recv until numbytes is 0 or less (connection close or error)
    while ((numbytes = recv(*sockfd, buf + total_bytes, MAXDATASIZE-1, 0)) > 0) {
      i++;
      total_bytes += numbytes;
      chunk += numbytes;
      // Add temp null terminator for str functions
      buf[total_bytes] = '\0';

      // If content_length hasn't been found
      if (!found_content_length) {
        char* length_header = strstr(buf, "Content-Length: ");
        if (length_header != NULL) {
          found_content_length = true;
          length_header += 16;
          char *afterHeader;

          content_length = strtol(length_header, &afterHeader, 10);
          v_verbose("Found Content-Length: %zu\n", content_length);
        }
      }

      if (found_content_length && !found_header_length) {
        char* end_of_header = strstr(buf, "\r\n\r\n");
        if (end_of_header != NULL) {
          found_header_length = true;
          header_length = char_distance(end_of_header + 4, buf);
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
    v_verbose("# of recvs: %d\n# of reallocs: %d\n", i, num_reallocs);
    //null terminate end of buffer
    buf[total_bytes] = '\0';
    printf("%s\n", (char *) buf);
    verbose("Total bytes: %d\n", total_bytes);
    return buf;
}
