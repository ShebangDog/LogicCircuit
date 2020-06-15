//
// Created by ayumu on 2020/06/12.
//

#include "debug.h"
#include <stdio.h>
#include <string.h>
#include "signal.h"
#include "../Analyzer/Model/node.h"
#include "../Analyzer/Model/operator.h"

void print_token(Token *token) {
    printf("%s ", token_kind_name[token->kind]);

    if (equal_end_token(*token)) {
        printf("\n");
        return;
    }

    print_token(token->nextToken);
}

void _print_node(Node *node, char *result) {
    if (node->left != NULL) _print_node(node->left, result);
    if (node->right != NULL) _print_node(node->right, result);
    sprintf(result, "%s%s ", result, node_kind_name[node->kind]);
}

void print_node(Node *node) {
    char buffer[256] = {0};

    _print_node(node, buffer);

    puts(buffer);
}
