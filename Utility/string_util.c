//
// Created by ayumu on 2020/06/25.
//

#include <string.h>

void join(int size1, int size2, char *joined, char splitted[size1][size2], int ch) {
    for (int index = 0; index < size1; ++index) {
        unsigned len = strlen(splitted[index]);
        char postfix[] = {(char) ch, '\0'};
        if (len == 0) break;

        strcat(joined, splitted[index]);
        strcat(joined, postfix);
    }
}

void split_space(int size1, int size2, char splitted[size1][size2], char *raw_string) {
    char *head = raw_string;
    for (int index = 0; index < size1 && head != NULL; ++index)  {
        char *p = strchr(head, ' ');
        char *last = (p == NULL ? &head[strlen(head)] : p);

        int len = last - head;
        strncpy(splitted[index], head, len);
        splitted[index][len] = '\0';

        head = (p == NULL ? NULL : last + 1);
    }
}

unsigned equal_substring(char *s1, char *s2, unsigned len) {
    return !strncmp(s1, s2, len);
}

