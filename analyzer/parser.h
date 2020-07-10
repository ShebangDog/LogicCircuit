//
// Created by ayumu on 2020/06/12.
//

#ifndef LOGICCIRCUIT_PARSER_H
#define LOGICCIRCUIT_PARSER_H

#include "model/node.h"
#include "model/token.h"
#include "../utility/either.h"

// <program> ::= ( <statement> )*
// <statement> ::= <assignment> ";"
// <assignment> ::= <circuit> ( "=" <circuit> )
//
// <circuit> ::= <signed-signal> (<binary> <signed-signal>)*
// <signed-signal> ::= (<unary>)* <primary>
// <primary> ::= <id> | <signal> | "(" <circuit> ")"
//
// <binary> ::= and | or | xor
// <signal> ::= 1 | 0
// <unary> :: = not
// <id> ::= [a-z]

Either(Node*) parse(Token *token);

static Either(Node*) block();

static Either(Node*) statement();

static Either(Node*) assignment();

static Either(Node*) circuit();

static Either(Node*) signed_signal();

static Either(Node*) primary();

static Either(Node*) id();

static Either(Node*) signal();

#endif //LOGICCIRCUIT_PARSER_H
