//
// Created by twilightskyasterisk on 6/16/20.
//

#include "evaluator.h"
#include "../Utility/converter.h"
#include <string.h>

Either(Signal) _eval(Node *node, char *stack);

Either(Signal) eval(Node *node) {
    char buffer[256] = {0};
    return ({
        Either(char) either = _eval(node, buffer);
        either;
    });
}

Either(Signal) _eval(Node *node, char *stack) {
    if (node->left != NULL) _eval(node->left, stack);
    if (node->right != NULL) _eval(node->right, stack);

    if (isoperator_node(*node)) {
        if (isunary_node(*node)) {
            Signal signal = char_to_signal(stack[strlen(stack) - 1]);
            Signal result = node_as_operator[node->kind].function.unary(signal);

            stack[strlen(stack) - 1] = '\0';
            sprintf(stack, "%s%u", stack, result.value);

            return ({
                Signal *stack_head_signal = stack_head_signal = calloc(sizeof(Signal), 1);
                *stack_head_signal = char_to_signal(stack[0]);

                Either(char) either = {.left = NULL, .right = (RIGHT_T *) stack_head_signal};
                either;
            });
        }

        if (isbinary_node(*node)) {
            Signal signal_right = char_to_signal(stack[strlen(stack) - 1]);
            Signal signal_left = char_to_signal(stack[strlen(stack) - 2]);

            Signal result = node_as_operator[node->kind].function.binary(signal_left, signal_right);

            stack[strlen(stack) - 2] = '\0';
            sprintf(stack, "%s%u", stack, result.value);

            return ({
                Signal *stack_head_signal = stack_head_signal = calloc(sizeof(Signal), 1);
                *stack_head_signal = char_to_signal(stack[0]);

                Either(char) either = {.left = NULL, .right = (RIGHT_T *) stack_head_signal};
                either;
            });
        }
    }

    if (issignal_node(*node)) {
        sprintf(stack, "%s%u", stack, signal_of(*node).value);
        return ({
            Signal *stack_head_signal = stack_head_signal = calloc(sizeof(Signal), 1);
            *stack_head_signal = char_to_signal(stack[0]);

            Either(char) either = {.left = NULL, .right = (RIGHT_T *) stack_head_signal};
            either;
        });
    }

    return error_occurred("error in evaluator");
}
