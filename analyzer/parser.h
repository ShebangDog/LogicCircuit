//
// Created by ayumu on 2020/06/12.
//

#ifndef LOGICCIRCUIT_PARSER_H
#define LOGICCIRCUIT_PARSER_H

#include "model/node.h"
#include "model/token.h"
#include "../utility/either.h"

// <circuit> ::= <signed-signal> (<binary> <signed-signal>)*
// <signed-signal> ::= (<unary>)* <primary>
// <primary> ::= <signal> | "(" <circuit> ")"
//
// <binary> ::= and | or | xor
// <signal> ::= 1 | 0
// <unary> :: = not

Either(Node*) parse(Token *token);

static Either(Node*) block();

static Either(Node*) circuit();

static Either(Node*) signed_signal();

static Either(Node*) primary();

static Either(Node*) signal();

#endif //LOGICCIRCUIT_PARSER_H
