//
// Created by Matthew Ferderber
// COMP445 Assignment #1
//

#include <stdio.h>
#include <string.h>


#include "response.h"

struct http_response parse_response(struct http_response *res, char *raw_res) {
  int line;
  char* token = strtok(raw_res, "\n");
  while(token != NULL) {
    //do
    line++;
    printf("on line %d: \n", line);
    int i;
    for(i = 0; token[i] != '\0'; i++) {
      printf("%c", token[i]);
    }
    token = strtok(raw_res, "\n");
  }
}
