//
// Created by Matthew Ferderber
// COMP445 Assignment #1
//

#include <stdio.h>


#include "file_reader.h"
#include "types.h"


int read_file(char* file_contents, char* file_name) {
    file_contents = malloc(sizeof(char) * MAXDATASIZE);
    FILE *fp;
    fp = fopen(file_name, "r");
    char c;
    int chunk = 0;
    int len = 0;

    while ((c = fgetc(fp)) != EOF) {
        chunk++;
        if (chunk > MAXDATASIZE) {
            file_contents = realloc(file_contents, sizeof(char) * (len + MAXDATASIZE));
            chunk = 0;
        }
        file_contents[len] = c;
        len++;
    }
    fclose(fp);
    return len;
}
