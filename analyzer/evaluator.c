//
// Created by twilightskyasterisk on 6/16/20.
//

#include "evaluator.h"
#include "../utility/converter.h"
#include <string.h>

Signal *variable_stack[32] = {NULL};

Either(Signal) _eval(Node *node, char *stack);

Either(Signal) eval(Node *node_array[]) {
    for(int index = 0;; ++index) {
        char buffer[256] = {0};
        Node *node = node_array[index];

        Either(Signal) either_signal = _eval(node, buffer);
        if (is_left(either_signal)) return either_signal;

        if (node_array[index + 1] == NULL) return either_signal;
    }
}

Either(Signal) _eval(Node *node, char *stack) {
    if (issignal_node(*node)) {
        sprintf(stack, "%s%u", stack, signal_of(*node).value);
    }

    if (isid_node(*node)) {
        Signal *variable_signal = variable_stack[node->offset];
        if (variable_signal == NULL) return error_occurred("undef");

        sprintf(stack, "%s%u", stack, variable_signal->value);
    }

    if (isassignment_node(*node)) {
        NodeKind kind = node->kind;

        if (node->left->kind != ND_ID) return error_occurred("left side value of assignment is not variable");

        int offset = node->left->offset;
        Either(Signal) either_signal = _eval(node->right, stack);

        if (is_left(either_signal)) return either_signal;
        node_as_operator[kind].function.assignment(variable_stack, offset, (Signal *) either_signal.right);
    }

    if (node->left != NULL) {
        Either(Signal) either_left = _eval(node->left, stack);
        if (is_left(either_left)) return either_left;
    }

    if (node->right != NULL) {
        Either(Signal) either_right = _eval(node->right, stack);
        if (is_left(either_right)) return either_right;
    }

    if (isoperator_node(*node)) {
        if (isunary_node(*node)) {
            Signal signal = char_to_signal(stack[strlen(stack) - 1]);
            Signal result = node_as_operator[node->kind].function.unary(signal);

            stack[strlen(stack) - 1] = '\0';
            sprintf(stack, "%s%u", stack, result.value);
        }

        if (isbinary_node(*node)) {
            Signal signal_right = char_to_signal(stack[strlen(stack) - 1]);
            Signal signal_left = char_to_signal(stack[strlen(stack) - 2]);

            Signal result = node_as_operator[node->kind].function.binary(signal_left, signal_right);

            stack[strlen(stack) - 2] = '\0';
            sprintf(stack, "%s%u", stack, result.value);
        }
    }

    return ({
        Signal *stack_head_signal = calloc(sizeof(Signal), 1);
        *stack_head_signal = char_to_signal(stack[0]);

        Either(char) either = {.left = NULL, .right = (RIGHT_T *) stack_head_signal};
        either;
    });
}
