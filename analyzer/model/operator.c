//
// Created by ayumu on 2020/06/12.
//
#include "operator.h"
#include "signal.h"

char *binary_name[] = {[and] = "and", [or] = "or", [xor] = "xor"};
char *unary_name[] = {[not] = "not"};
char *assignment_name = "=";

int binary_start = and;
int unary_start = not;

int binary_end = xor;
int unary_end = not;

Signal not_operator(Signal signal) {
    return not_signal(signal);
}

Signal or_operator(Signal left, Signal right) {
    return ({
        Signal signal = {.value = left.value | right.value};

        signal;
    });
}

Signal and_operator(Signal left, Signal right) {
    return ({
        Signal signal = {.value = left.value & right.value};

        signal;
    });
}

Signal xor_operator(Signal left, Signal right) {
    return ({
       Signal signal = {.value = left.value ^ right.value};

       signal;
    });
}

void assignment_operator(Signal *to[], int offset, Signal *from) {
    to[offset] = from;
}