//
// Created by twilightskyasterisk on 6/16/20.
//

#include "evaluator.h"
#include "../Utility/converter.h"
#include <string.h>

char _eval(Node *node, char *stack);

Signal eval(Node *node) {
    char buffer[256] = {0};
    char result = _eval(node, buffer);

    return char_to_signal(result);
}

char _eval(Node *node, char *stack) {
    if (node->left != NULL) _eval(node->left, stack);
    if (node->right != NULL) _eval(node->right, stack);

    if (isoperator_node(*node)) {
        if (isunary_node(*node)) {
            Signal signal = char_to_signal(stack[strlen(stack) - 1]);
            Signal result = node_as_operator[node->kind].function.unary(signal);

            stack[strlen(stack) - 1] = '\0';
            sprintf(stack, "%s%u", stack, result.value);

            return stack[0];
        }

        if (isbinary_node(*node)) {
            Signal signal_right = char_to_signal(stack[strlen(stack) - 1]);
            Signal signal_left = char_to_signal(stack[strlen(stack) - 2]);

            Signal result = node_as_operator[node->kind].function.binary(signal_left, signal_right);

            stack[strlen(stack) - 2] = '\0';
            sprintf(stack, "%s%u", stack, result.value);

            return stack[0];
        }
    }

    if (issignal_node(*node)) {
        sprintf(stack, "%s%u", stack, signal_of(*node).value);
        return stack[0];
    }

    puts("error / debug");
    exit(1);
}
