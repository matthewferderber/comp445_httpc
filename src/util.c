//
// Created by Matthew Ferderber
// COMP445 Assignment 1
//

#include <stdio.h>
#include <stdarg.h>
#include <stdbool.h>

#include "util.h"

bool httpc_verbose = false;

// Prints verbose infornation if flag is enabled
void verbose(char *format, ...) {
    if (httpc_verbose) {
        va_list args;
        va_start(args, format);
        vfprintf(stdout, format, args);
        va_end(args);
    }
}
void set_verbose() {
    httpc_verbose = true;
}
