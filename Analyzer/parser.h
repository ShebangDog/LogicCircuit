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

struct Parser {
    Node *tree;
} parser;

void parse(Token *token);

static Node *circuit(Token *token);

static Node *primary(Token *token);

static Node *signed_signal(Token *token);

static Node *unary(Token *token);

static Node *binary(Token *token);

static Node *signal(Token *token);

#endif //LOGICCIRCUIT_PARSER_H
