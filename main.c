#include "Analyzer/lexer.h"
#include "Analyzer/parser.h"
#include "Utility/debug.h"
#include "Analyzer/evaluator.h"

void left_case(Either(Token | Node | Signal) either);

typedef struct {
    unsigned value;
} ResultCalculate;

Either(ResultCalculate) calculate(int size1, int size2, char splitted[size1][size2]) {
    char joined[1024] = {0};

    Either(Token*) either_token = tokenize(joined);
    if (is_left(either_token)) return either_token;

    if (is_right(either_token)) {
        Token *token = (Token *) either_token.right;
        print_token(token);

        Either(Node*) either_node = parse(token);
        if (is_left(either_node)) return either_node;

        if (is_right(either_node)) {
            Node *node = (Node *) either_node.right;
            print_node(node);

            Either(Signal) either_signal = eval(node);
            if (is_left(either_signal)) return either_signal;

            if (is_right(either_signal)) {
                Signal *signal = (Signal *) either_signal.right;

                return ({
                    ResultCalculate result = {.value = signal->value};
                    Either(ResultCalculate) either_result = {.left = NULL, .right = (RIGHT_T *) &result};
                    either_result;
                });
            }
        }
    }

    return error_occurred("unknown error");
}

int main(int argc, char *argv[]) {
    char string[] = "(((1 xor not 1) and 0) or not not not not 1)";

    Either(Token*) either_token = tokenize(string);
    left_case(either_token);

    if (is_right(either_token)) {
        Token *token = (Token *) either_token.right;

        Either(Node*) either_node = parse(token);
        left_case(either_node);

        if (is_right(either_node)) {
            Node *node = (Node *) either_node.right;
            char tree_string[256] = {0};
            print_tree(node, tree_string);

            Either(Signal) either_signal = eval(node);
            left_case(either_signal);

            if (is_right(either_signal)) {
                Signal *signal = (Signal *) either_signal.right;
                print_signal(*signal);
            }
        }
    }

    return 0;
}

void left_case(Either(Token | Node | Signal) either) {
    if (is_left(either)) {
        puts(either.left);
        exit(1);
    }
}