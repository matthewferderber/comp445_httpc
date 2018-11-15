//
// Created by Matthew Ferderber
// COMP445 Assignment 1
//

#ifndef A3_40010150_UTIL_H
#define A3_40010150_UTIL_H

#include <stdlib.h>
#include <stdbool.h>

void verbose(const char *format, ...);
void v_verbose(const char *format, ...);
void set_verbose();
void set_v_verbose();
bool is_verbose();
size_t char_distance(char *end, char *start);

#endif //A3_40010150_UTIL_H
