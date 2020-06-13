//
// Created by ayumu on 2020/06/12.
//
#include "operator.h"

char *binary_name[] = {[and] = "and", [or] = "or", [xor] = "xor"};
char *unary_name[] = {[not] = "not"};

int binary_start = and;
int unary_start = not;

int binary_end = xor;
int unary_end = not;

