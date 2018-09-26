//
// Created by Matthew Ferderber
// COMP445 Assignment 1
//

#include <stdio.h>
#include <stdarg.h>
#include <stdbool.h>

#include "util.h"

bool httpc_verbose = false;
bool httpc_v_verbose = false;

void va_verbose(const char *format, va_list args) {
        vfprintf(stdout, format, args);
}

// Prints verbose information if flag is enabled
void verbose(const char *format, ...) {
    if (httpc_verbose) {
        va_list args;
        va_start(args, format);
        va_verbose(format, args);
        va_end(args);
    }
}

// Prints extra verbose information
void v_verbose(const char *format, ...) {
    if (httpc_v_verbose && httpc_verbose) {
        va_list args;
        va_start(args, format);
        va_verbose(format, args);
        va_end(args);
    }
}

void set_verbose() {
    httpc_verbose = true;
}

void set_v_verbose() {
    httpc_v_verbose = true;
}

size_t char_distance(char *end, char *start) {
    return (end - start) * sizeof(char);
}
