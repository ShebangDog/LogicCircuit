//
// Created by twilightskyasterisk on 6/16/20.
//

#include "evaluator.h"
#include "Model/node.h"
#include "Model/signal.h"
#include <string.h>

Signal char_to_signal(char ch) {
    return ({
        Signal result = {.value = ch - '0'};

        result;
    });
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
        sprintf(stack, "%s%u", stack, signal_of(*node).value);
        return;
    }

    puts("error / debug");
    exit(1);
}

void eval(Node *node) {
    char buffer[256] = {0};
    _eval(node, buffer);

    evaluator.signal = char_to_signal(buffer[0]);
}