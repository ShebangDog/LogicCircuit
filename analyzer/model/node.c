//
// Created by ayumu on 2020/06/13.
//

#include "node.h"
#include "../../utility/converter.h"
#include "../../utility/string_util.h"

char *node_kind_name[] = {
        [ND_ROOT] = "{",
        [ND_END] = "}",
        [ND_SIGNAL_ON] = "1",
        [ND_SIGNAL_OFF] = "0",
        [ND_OPENING_BRACKET] = "(",
        [ND_CLOSING_BRACKET] = ")",
        [ND_ASSIGNMENT] = "=",
        [ND_ID] = "var",
        [ND_NOT] = "not",
        [ND_AND] = "and",
        [ND_OR] = "or",
        [ND_XOR] = "xor"
};

Operator node_as_operator[ND_END + 1] = {
        [ND_ROOT] = NONE_OPERATOR,
        [ND_END] = NONE_OPERATOR,
        [ND_SIGNAL_ON] = NONE_OPERATOR,
        [ND_SIGNAL_OFF] = NONE_OPERATOR,
        [ND_OPENING_BRACKET] = NONE_OPERATOR,
        [ND_CLOSING_BRACKET] = NONE_OPERATOR,
        [ND_ID] = NONE_OPERATOR,
        [ND_ASSIGNMENT] = {.name = "assignment", .function.assignment = assignment_operator},
        [ND_NOT] = {.name = "not", .function.unary = not_operator},
        [ND_AND] = {.name = "and", .function.binary = and_operator},
        [ND_OR] = {.name = "or", .function.binary = or_operator},
        [ND_XOR] = {.name = "xor", .function.binary = xor_operator}
};

int node_kind_start = ND_ROOT;
int node_kind_end = ND_END;

Node *new_node(NodeKind kind, int offset, Node *left, Node *right) {
    Node *node = calloc(sizeof(Node), 1);

    node->kind = kind;
    node->offset = (node->kind == ND_ID) ? offset : -1;
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

Node *new_node_assignment(Node *left, Node *right) {
    return new_node(ND_ASSIGNMENT, 0, left, right);
}

Node *new_node_id(char name) {
    return new_node(ND_ID, name - 'a', NULL, NULL);
}

unsigned isequal_node(Node node) {
    return node.kind == ND_ASSIGNMENT;
}

unsigned isid_node(Node node) {
    return node.kind == ND_ID;
}

unsigned issignal_node(Node node) {
    NodeKind kind = node.kind;

    return kind == ND_SIGNAL_OFF || kind == ND_SIGNAL_ON;
}

unsigned isoperator_node(Node node) {
    return isunary_node(node) || isbinary_node(node);
}

unsigned isbinary_node(Node node) {
    NodeKind kind = node.kind;

    for (int i = binary_start; i < binary_end + 1; ++i) {
        if (equal_string(binary_name[i], node_kind_name[kind])) return true;
    }

    return false;
}

unsigned isunary_node(Node node) {
    NodeKind kind = node.kind;

    for (int i = unary_start; i < unary_end + 1; ++i) {
        if (equal_string(unary_name[i], node_kind_name[kind])) return true;
    }

    return false;
}

unsigned isassignment_node(Node node) {
    NodeKind kind = node.kind;

    return equal_string(assignment_name, node_kind_name[kind]);
}

unsigned equal_root_node(Node node) {
    return node.kind == ND_ROOT;
}

unsigned equal_end_node(Node node) {
    return node.kind == ND_END;
}

Signal signal_of(Node node) {
    NodeKind kind = node.kind;
    if (kind == ND_SIGNAL_ON || kind == ND_SIGNAL_OFF) {
        return kind == ND_SIGNAL_ON ? on : off;
    } else {
        puts("error on signal_of");
        exit(1);
    }
}
