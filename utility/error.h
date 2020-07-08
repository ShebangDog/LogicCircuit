//
// Created by ayumu on 2020/06/25.
//

#ifndef LOGICCIRCUIT_ERROR_H
#define LOGICCIRCUIT_ERROR_H

#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

__attribute__((noreturn)) void error(const char *fmt, ...);

#endif //LOGICCIRCUIT_ERROR_H
