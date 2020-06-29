//
// Created by ayumu on 2020/06/25.
//

#ifndef LOGICCIRCUIT_STRING_UTIL_H
#define LOGICCIRCUIT_STRING_UTIL_H

void join(int size1, int size2, char *joined, char splitted[size1][size2], int ch);

void split_space(int size1, int size2, char splitted[size1][size2], char *raw_string);

unsigned equal_substring(char *s1, char *s2, unsigned len);

unsigned equal_string(char *s1, char *s2);

#endif //LOGICCIRCUIT_STRING_UTIL_H
