//
// Created by ayumu on 2020/06/28.
//
#include <stddef.h>
#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include "either.h"

bool is_right(struct Either either) {
    return either.right != NULL;
}

bool is_left(struct Either either) {
    return either.left != NULL;
}

Either(Error) error_occurred(const char *fmt, ...) {
    char *message = calloc(sizeof(char), 256);
    va_list ap;
    va_start(ap, fmt);
    vsprintf(message, fmt, ap);

    return (Either(Error)) {.left = message, .right = NULL};
}
