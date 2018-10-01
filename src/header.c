//
// Created by Matthew Ferderber
// COMP445 Assignment #1
//

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "header.h"

HttpHeader* parse_header(char* raw_head) {
  HttpHeader* h = malloc(sizeof(HttpHeader));
  int k = 0;
  char *key = NULL;
  char *val = NULL;
  for (k = 0; raw_head[k] != '\0'; k++) {
      if (raw_head[k] == ':') {
          key = malloc(sizeof(char) * k + 1);
          memcpy(key, raw_head, k);
          key[k] = '\0';
          break;
      }
  }
  if (key != NULL) {
      size_t val_len = strlen(raw_head + k + 2);
      val = malloc(sizeof(char) * val_len + 1);
      memcpy(val, raw_head + k + 2, val_len);
      val[val_len] = '\0';
      // int key_len = k;
      h->key = key;
      h->value = val;
  }
  return h;
}

void print_headers(HttpResponse* r) {
    int i;
    for(i = 0; i < r->num_headers; i++) {
        printf("%s: %s", r->http_headers[i].key, r->http_headers[i].value);
    }
}