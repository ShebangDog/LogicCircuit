//
// Created by ayumu on 2020/06/12.
//

#ifndef LOGICCIRCUIT_PARSER_H
#define LOGICCIRCUIT_PARSER_H

#include "Model/node.h"
#include "Model/token.h"

// <circuit> ::= <primary> <binary> <primary>
// <primary> ::= <signed-signal> | "(" <circuit> ")"
// <signed-signal> ::= <signal> | <unary> <signed-signal>
// <unary> ::= not
// <binary> ::= and | xor | or
// <signal> ::= 1 | 0

Node* parse(Token *token);

static Node *block();

static Node *circuit();

static Node *primary();

static Node *signed_signal();

static Node *unary();

static Node *binary();

static Node *signal();

#endif //LOGICCIRCUIT_PARSER_H
