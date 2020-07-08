//
// Created by ayumu on 2020/06/12.
//

#ifndef LOGICCIRCUIT_PARSER_H
#define LOGICCIRCUIT_PARSER_H

#include "Model/node.h"
#include "Model/token.h"
#include "../Utility/either.h"

// <circuit> ::= <primary> <binary> <primary>
// <primary> ::= <signed-signal> | "(" <circuit> ")"
// <signed-signal> ::= <signal> | <unary> <signed-signal>
// <unary> ::= not
// <binary> ::= and | xor | or
// <signal> ::= 1 | 0

Either(Node*) parse(Token *token);

static Either(Node*) block();

static Either(Node*) circuit();

static Either(Node*) primary();

static Either(Node*) signed_signal();

static Either(Node*) signal();

#endif //LOGICCIRCUIT_PARSER_H
