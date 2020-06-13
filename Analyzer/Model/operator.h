//
// Created by ayumu on 2020/06/12.
//

#ifndef LOGICCIRCUIT_OPERATOR_H
#define LOGICCIRCUIT_OPERATOR_H

enum Binary {
    and, or, xor
};

enum Unary {
    not
};

char *binary_name[xor + 1];
char *unary_name[not + 1];

int binary_start;
int unary_start;

int binary_end;
int unary_end;

#endif //LOGICCIRCUIT_OPERATOR_H
