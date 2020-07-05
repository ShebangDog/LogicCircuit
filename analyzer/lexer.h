//
// Created by twilightskyasterisk on 5/13/20.
//

#ifndef LOGICCERCUIT_LEXER_H
#define LOGICCERCUIT_LEXER_H

#include "model/token.h"
#include "../utility/either.h"

static Either(Token*) _tokenize(char *str, Token *token);

Either(Token*) tokenize(char *str);

#endif //LOGICCERCUIT_LEXER_H
