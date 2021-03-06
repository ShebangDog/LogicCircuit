//
// Created by ayumu on 2020/06/12.
//

#include "token.h"
#include "../../utility/string_util.h"
#include <stdlib.h>
#include <string.h>

int token_kind_start = T_ROOT;
int token_kind_end = T_END;
char *token_kind_name[] = {
        [T_ROOT] = "{",
        [T_SIGNAL] = "<0|1>",
        [T_BRACKET] = "<(|)>",
        [T_EQUAL] = "<=>",
        [T_SEMICOLON] = ";",
        [T_OPERATOR] = "<and|or|xor|not>",
        [T_ID] = "<a-z>",
        [T_END] = "}"
};

Token *new_token(Token token, Token *parent) {
    Token *t = calloc(sizeof(Token), 1);
    parent->next_token = t;

    t->kind = token.kind;
    strncpy(t->value, token.value, strlen(token.value));

    return t;
}

unsigned equal_root_token(Token token) {
    return token.kind == ROOT_TOKEN.kind;
}

unsigned equal_end_token(Token token) {
    return token.kind == END_TOKEN.kind;
}

unsigned isbinary_token(Token token) {
    if (token.kind == T_OPERATOR) {
        for (int i = binary_start; i < binary_end + 1; ++i) {
            if (equal_substring(binary_name[i], token.value, strlen(token.value))) return true;
        }
    }

    return false;
}

unsigned isunary_token(Token token) {
    if (token.kind == T_OPERATOR) {
        for (int i = unary_start; i < unary_end + 1; ++i) {
            if (equal_substring(unary_name[i], token.value, strlen(token.value))) return true;
        }
    }

    return false;
}

unsigned issignal_token(Token token) {
    return token.kind == T_SIGNAL;
}

unsigned isid_token(Token token) {
    return token.kind == T_ID;
}

unsigned issemicolon_token(Token token) {
    return token.kind == T_SEMICOLON;
}