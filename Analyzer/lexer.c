//
// Created by ayumu on 2020/06/12.
//

#include "Model/token.h"
#include "lexer.h"
#include "../Utility/string_util.h"
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

struct Lexer lexer = {.token = &ROOT_TOKEN};

char *consume_operator_lexer(char *str);

unsigned issignal(char ch);

unsigned isoperator(char *str);

unsigned isbracket(char ch);

void tokenize(char *str) {
    Token *root = calloc(sizeof(Token), 1);
    *root = ROOT_TOKEN;
    lexer.token = root;
    _tokenize(str, lexer.token);
}

static void _tokenize(char *str, Token *token) {

    if (*str == '\0') {
        Token t = END_TOKEN;
        new_token(t, token);

        return;
    }

    if (isspace(*str)) {
        return _tokenize(str + 1, token);
    }

    if (issignal(*str)) {
        return _tokenize(str + 1, ({
            Token t = {.kind = T_SIGNAL, .value = {str[0], '\0'}};
            new_token(t, token);
        }));
    }

    if (isbracket(*str)) {
        return _tokenize(str + 1, ({
            Token t = {.kind = T_BRACKET, .value = {str[0], '\0'}};
            new_token(t, token);
        }));
    }

    if (isoperator(str)) {
        char *next = consume_operator_lexer(str);
        return _tokenize(next, ({
            Token t = {.kind = T_OPERATOR, .value = 0};
            int len = next - str;

            strncpy(t.value, str, len);
            new_token(t, token);
        }));
    }

    puts("error in tokenize");
    exit(1);
}

unsigned issignal(char ch) {
    return ch == '1' || ch == '0';
}

unsigned isoperator(char *str) {
    for (int i = binary_start; i < binary_end + 1; ++i) {
        if (equal_substring(binary_name[i], str, strlen(binary_name[i]))) return true;
    }

    for (int i = unary_start; i < unary_end + 1; ++i) {
        if (equal_substring(unary_name[i], str, strlen(unary_name[i]))) return true;
    }

    return false;
}

unsigned isbracket(char ch) {
    return ch == '(' || ch == ')';
}

char *consume_operator_lexer(char *str) {
    for (int i = binary_start; i < binary_end + 1; ++i) {
        unsigned len = strlen(binary_name[i]);
        if (equal_substring(binary_name[i], str, len)) return str + len;
    }

    for (int i = unary_start; i < unary_end + 1; ++i) {
        unsigned len = strlen(unary_name[i]);
        if (equal_substring(unary_name[i], str, len)) return str + len;
    }

    exit(1);
}