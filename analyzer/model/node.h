//
// Created by ayumu on 2020/06/12.
//

#ifndef LOGICCIRCUIT_NODE_H
#define LOGICCIRCUIT_NODE_H

#include <stdlib.h>
#include <stdio.h>
#include "operator.h"

typedef enum {
    ND_ROOT,
    ND_AND,
    ND_OR,
    ND_XOR,
    ND_NOT,
    ND_SIGNAL_OFF,
    ND_SIGNAL_ON,
    ND_OPENING_BRACKET,
    ND_CLOSING_BRACKET,
    ND_ASSIGNMENT,
    ND_ID,
    ND_END
} NodeKind;

int node_kind_start;
int node_kind_end;

Operator node_as_operator[ND_END + 1];
char *node_kind_name[ND_END + 1];

typedef struct node {
    struct node *left;
    struct node *right;

    int offset;
    NodeKind kind;
} Node;

Node *new_node_assignment(Node *left, Node *right);

Node *new_node_binary(NodeKind kind, Node *left, Node *right);

Node *new_node_signal(int value);

Node *new_node_signed_signal(NodeKind kind, Node *right);

Node *new_node_id(char name);

Node *new_node(NodeKind kind, int offset, Node *left, Node *right);

unsigned issignal_node(Node node);

unsigned isequal_node(Node node);

unsigned isid_node(Node node);

unsigned isoperator_node(Node node);

unsigned isbinary_node(Node node);

unsigned isassignment_node(Node node);

unsigned isunary_node(Node node);

unsigned equal_root_node(Node node);

unsigned equal_end_node(Node node);

Signal signal_of(Node node);

#endif //LOGICCIRCUIT_NODE_H
