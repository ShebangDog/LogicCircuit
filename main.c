#include "Analyzer/lexer.h"
#include "Analyzer/parser.h"
#include "Utility/debug.h"
#include "Analyzer/evaluator.h"

void left_case(Either(Token | Node | Signal) either);

int main(int argc, char *argv[]) {
//    tokenize("1 xor not not 1 or 1");
//    tokenize("1 or 0 and 0");
//    tokenize("1 and 0 or 1");
//"not not not 1 xor (1 or 1)"
    char string[] = "1 and 0 or not not notnotnot 1";
    puts(string);

    Either(Token*) either_token = tokenize(string);
    left_case(either_token);

    if (is_right(either_token)) {
        Token *token = (Token *) either_token.right;
        print_token(token);

        Either(Node*) either_node = parse(token);
        left_case(either_node);

        if (is_right(either_node)) {
            Node *node = (Node *) either_node.right;
            print_node(node);

            Either(Signal) either_signal = eval(node);
            left_case(either_signal);

            if (is_right(either_signal)) {
                Signal* signal = (Signal *) either_signal.right;

                printf("%u\n", signal->value);
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