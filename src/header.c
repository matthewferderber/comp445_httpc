//
// Created by Matthew Ferderber
// COMP445 Assignment #3
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
      raw_head[k + 1] == ' ' ? k++ : 0;
      size_t val_len = strlen(raw_head + k + 1);
      val = malloc(sizeof(char) * (val_len + 1));
      memcpy(val, raw_head + k + 1, val_len);
      val[val_len] = '\0';
      h->key = key;
      h->value = val;
  }
  return h;
}

void print_headers(HttpHeader* h, int num_headers) {
    int i;
    for(i = 0; i < num_headers; i++) {
        printf("%s: %s\n", h[i].key, h[i].value);
    }
}

void http_header_new(HttpHeader* h, char* key, char* value) {
    h = malloc(sizeof(HttpHeader));
    h->key = key;
    h->value = value;
}
void http_header_destroy(HttpHeader* h) {
    free(h->key);
    free(h->value);
    //free(h);
    h = NULL;
}

