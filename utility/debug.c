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

    print_token(token->next_token);
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

//void _print_tree(Node *node, char *result, int left_level, int right_level) {
//    sprintf(result, "%s%s\n", result, node_kind_name[node->kind]);
//
//    for (int i = 0; i < (left_level + right_level) / 2; ++i) sprintf(result, "%s%s", result, " ");
//
//    sprintf(result, "%sL", result);
//
//    for (int i = 0; i < (left_level + right_level) / 2; ++i) sprintf(result, "%s%s", result, "");
//
//    if (node->left != NULL) _print_tree(node->left, result, left_level + 1, right_level);
//    if (node->right != NULL) _print_tree(node->right, result, left_level, right_level + 1);
//}

void _print_tree(Node *node, char *result, int level) {
    sprintf(result, "%s\n", result);

    //if (node->right == NULL) sprintf(result, "%s%s", result, "|");
    for (int i = 0; i < level - 1; ++i) sprintf(result, "%s%s", result, " ");

    if (level != 0) sprintf(result, "%sL", result);
    //sprintf(result, (level == 0 ? "%s\n" : "%s\nL"), result);

    sprintf(result, "%s%s", result, node_kind_name[node->kind]);

    if (node->left != NULL) _print_tree(node->left, result,  level+ 1);
    if (node->right != NULL) _print_tree(node->right, result,  level+ 1);
}

void print_tree(Node *node, char *result) {
    _print_tree(node, result, 0);
}

void print_signal(Signal signal) {
    printf("%u\n", signal.value);
}
