//
// Created by ayumu on 2020/06/12.
//

#ifndef LOGICCIRCUIT_OPERATOR_H
#define LOGICCIRCUIT_OPERATOR_H

#include "signal.h"

#define NONE_OPERATOR {.name="none_operator",.function=NULL}

enum Binary {
    and, or, xor
};

enum Unary {
    not
};

typedef struct {
    char name[16];

    union {
        Signal (*binary)(Signal, Signal);

        void (*assignment)(Signal *[], int, Signal*);

        Signal (*unary)(Signal);
    } function;
} Operator;

char *binary_name[xor + 1];
char *unary_name[not + 1];
char *assignment_name;

int binary_start;
int unary_start;

int binary_end;
int unary_end;

Signal not_operator(Signal signal);

Signal or_operator(Signal left, Signal right);

Signal and_operator(Signal left, Signal right);

Signal xor_operator(Signal left, Signal right);

void assignment_operator(Signal *to[], int offset, Signal *from);

#endif //LOGICCIRCUIT_OPERATOR_H
