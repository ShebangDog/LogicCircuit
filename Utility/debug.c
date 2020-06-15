//
// Created by ayumu on 2020/06/12.
//

#include "debug.h"
#include <stdio.h>
#include <string.h>
#include "signal.h"
#include "../Analyzer/Model/node.h"
#include "../Analyzer/Model/operator.h"

Signal char_to_signal(char ch) {
    return ({
        Signal result = {.value = ch - '0'};

        result;
    });
}

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

void _eval(Node *node, char *stack) {
    if (node->left != NULL) _eval(node->left, stack);
    if (node->right != NULL) _eval(node->right, stack);

    if (isoperator_node(*node)) {
        if (isunary_node(*node)) {
            Signal signal = char_to_signal(stack[strlen(stack) - 1]);
            Signal result = node_as_operator[node->kind].function.unary(signal);

            stack[strlen(stack) - 1] = '\0';
            sprintf(stack, "%s%u", stack, result.value);

            return;
        }

        if (isbinary_node(*node)) {
            Signal signal_right = char_to_signal(stack[strlen(stack) - 1]);
            Signal signal_left = char_to_signal(stack[strlen(stack) - 2]);

            Signal result = node_as_operator[node->kind].function.binary(signal_left, signal_right);

            stack[strlen(stack) - 2] = '\0';
            sprintf(stack, "%s%u", stack, result.value);

            return;
        }
    }

    if (issignal_node(*node)) {
        sprintf(stack, "%s%u", stack, signal_of(node->kind).value);
        return;
    }

    puts("error / debug");
    exit(1);
}

unsigned eval(Node *node) {
    char buffer[256] = {0};
    _eval(node, buffer);

    return char_to_signal(buffer[0]).value;
}