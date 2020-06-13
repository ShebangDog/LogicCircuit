//
// Created by ayumu on 2020/06/13.
//

#include "node.h"
#include "../../Utility/converter.h"

char *node_kind_name[ND_END + 1] = {
        [ND_ROOT] = "{",
        [ND_END] = "}",
        [ND_SIGNAL_ON] = "1",
        [ND_SIGNAL_OFF] = "0",
        [ND_NOT] = "not",
        [ND_AND] = "and",
        [ND_OR] = "or",
        [ND_XOR] = "xor"
};

int node_kind_start = ND_ROOT;
int node_kind_end = ND_END;

Node *new_node(NodeKind kind, Node *left, Node *right) {
    Node *node = calloc(sizeof(Node), 1);

    node->kind = kind;
    node->left = left;
    node->right = right;

    return node;
}

Node *new_node_binary(NodeKind kind, Node *left, Node *right) {
    Node *node = calloc(sizeof(Node), 1);

    node->kind = kind;
    node->left = left;
    node->right = right;

    return node;
}

Node *new_node_signed_signal(NodeKind kind, Node *right) {
    Node *node = calloc(sizeof(Node), 1);

    node->kind = kind;
    node->right = right;
    node->left = NULL;

    return node;
}

Node *new_node_signal(int value) {
    Node *node = calloc(sizeof(Node), 1);

    node->kind = (value == 1 ? ND_SIGNAL_ON : ND_SIGNAL_OFF);
    node->left = NULL;
    node->right = NULL;

    return node;
}

unsigned equal_root_node(Node node) {
    return node.kind == ND_ROOT;
}

unsigned equal_end_node(Node node) {
    return node.kind == ND_END;
}