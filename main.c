#include "analyzer/lexer.h"
#include "analyzer/parser.h"
#include "utility/debug.h"

void left_case(Either(Token | Node | Signal) either);

int main(int argc, char *argv[]) {
    char string[] = "a = not ((1) xor not 1)";

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

//            Either(Signal) either_signal = eval(node);
//            left_case(either_signal);
//
//            if (is_right(either_signal)) {
//                Signal *signal = (Signal *) either_signal.right;
//                print_signal(*signal);
//            }
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
