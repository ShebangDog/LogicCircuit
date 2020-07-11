//
// Created by ayumu on 2020/06/12.
//

#ifndef LOGICCERCUIT_TOKEN_H
#define LOGICCERCUIT_TOKEN_H

#include <stddef.h>
#include <stdbool.h>
#include "operator.h"

typedef enum {
    T_ROOT,
    T_SIGNAL,
    T_BRACKET,
    T_SEMICOLON,
    T_EQUAL,
    T_OPERATOR,
    T_ID,
    T_END
} TokenKind;

typedef struct Token {
    TokenKind kind;
    char value[16];

    struct Token *next_token;
} Token;

static Token ROOT_TOKEN = {.kind = T_ROOT, .value = "identify_root"};
static Token END_TOKEN = {.kind = T_END, .value = "identify_end"};

int token_kind_start;
int token_kind_end;
char *token_kind_name[T_END + 1];

Token *new_token(Token token, Token *parent);

unsigned equal_root_token(Token token);

unsigned equal_end_token(Token token);

unsigned isbinary_token(Token token);

unsigned isunary_token(Token token);

unsigned issignal_token(Token token);

unsigned issemicolon_token(Token token);

unsigned isid_token(Token token);

#endif //LOGICCERCUIT_TOKEN_H
