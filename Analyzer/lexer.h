//
// Created by twilightskyasterisk on 5/13/20.
//

#ifndef LOGICCERCUIT_LEXER_H
#define LOGICCERCUIT_LEXER_H

#include "Model/token.h"

struct Lexer {
    Token *token;
} lexer;

static Token* _tokenize(char *str, Token *token);

Token* tokenize(char *str);

#endif //LOGICCERCUIT_LEXER_H
