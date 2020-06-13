//
// Created by ayumu on 2020/06/12.
//

#ifndef LOGICCIRCUIT_NODE_H
#define LOGICCIRCUIT_NODE_H

#include <stdlib.h>
#include <stdio.h>

typedef enum {
    ND_ROOT, ND_AND, ND_OR, ND_XOR, ND_NOT, ND_SIGNAL_OFF, ND_SIGNAL_ON, ND_END
} NodeKind;

int node_kind_start;
int node_kind_end;

char *node_kind_name[ND_END + 1];

typedef struct node {
    struct node *left;
    struct node *right;

    NodeKind kind;
} Node;

Node *new_node_binary(NodeKind kind, Node *left, Node *right);

Node *new_node_signal(int value);

Node *new_node_signed_signal(NodeKind kind, Node *right);

Node *new_node(NodeKind kind, Node *left, Node *right);

unsigned equal_root_node(Node node);

unsigned equal_end_node(Node node);

#endif //LOGICCIRCUIT_NODE_H
