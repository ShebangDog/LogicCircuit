//
// Created by ayumu on 2020/06/12.
//

#ifndef LOGICCIRCUIT_DEBUG_H
#define LOGICCIRCUIT_DEBUG_H

#include "../Analyzer/Model/token.h"
#include "../Analyzer/Model/node.h"

void print_token(Token *token);

void print_node(Node *node);

void print_tree(Node *node, char *result);

void print_signal(Signal signal);

void test();

#endif //LOGICCIRCUIT_DEBUG_H
