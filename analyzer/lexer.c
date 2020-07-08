//
// Created by ayumu on 2020/06/12.
//

#include "model/token.h"
#include "lexer.h"
#include "../utility/string_util.h"
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

Either(char*) consume_operator_lexer(char *str);

unsigned issignal(char ch);

unsigned isequal(char ch);

unsigned isoperator(char *str);

unsigned isid(char ch);

unsigned isbracket(char ch);

Token *root_token;

Either(Token*) tokenize(char *str) {
    root_token = root_token == NULL ? calloc(sizeof(Token), 1) : root_token;
    *root_token = ROOT_TOKEN;

    return _tokenize(str, root_token);
}

static Either(Token*) _tokenize(char *str, Token *token) {

    if (*str == '\0') {
        Token t = END_TOKEN;
        new_token(t, token);

        return ({
            Either(Token*) either = {.left = NULL, .right = (RIGHT_T *) root_token};
            either;
        });
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
        Either(char *) either = consume_operator_lexer(str);
        if (is_left(either)) return either;
        if (is_right(either)) {
            char *next = (char *) either.right;
            return _tokenize(next, ({
                Token t = {.kind = T_OPERATOR, .value = 0};
                long len = next - str;

                strncpy(t.value, str, len);
                new_token(t, token);
            }));
        }
    }

    if (isequal(*str)) {
        return _tokenize(str + 1, ({
            Token t = {.kind = T_EQUAL, .value = {str[0], '\0'}};
            new_token(t, token);
        }));
    }

    if (isid(*str)) {
        return _tokenize(str + 1, ({
            Token t = {.kind = T_ID, .value = {str[0], '\0'}};
            new_token(t, token);
        }));
    }

    return error_occurred("error in tokenize");
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

Either(char *) consume_operator_lexer(char *str) {
    for (int i = binary_start; i < binary_end + 1; ++i) {
        unsigned len = strlen(binary_name[i]);
        if (equal_substring(binary_name[i], str, len))
            return ({
                Either(char*) either = {.right = (RIGHT_T *) (str + len)};
                either;
            });
    }

    for (int i = unary_start; i < unary_end + 1; ++i) {
        unsigned len = strlen(unary_name[i]);
        if (equal_substring(unary_name[i], str, len))
            return ({
                Either(char*) either = {.right = (RIGHT_T *) (str + len)};
                either;
            });
    }

    return ({
        char message[256] = {0};
        sprintf(message, "expect operator but got %s", str);

        error_occurred(message);
    });
}

unsigned isid(char ch) {
    return 'a' <= ch && ch <= 'z';
}

unsigned isequal(char ch) {
    return ch == '=';
}