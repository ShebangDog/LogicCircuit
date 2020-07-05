//
// Created by ayumu on 2020/06/25.
//

#include "error.h"

__attribute__((noreturn)) void error(const char *fmt, ...) {
    va_list ap;
    va_start(ap, fmt);
    vfprintf(stderr, fmt, ap);
    fprintf(stderr, "\n");
    exit(1);
}