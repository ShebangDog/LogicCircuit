#include "analyzer/lexer.h"
#include "analyzer/parser.h"
#include "utility/debug.h"
#include "analyzer/evaluator.h"

void left_case(Either(Token | Node | Signal) either);

int main(int argc, char *argv[]) {
    char string[] = "a = (not not 1 and 0) or 1; a and 1;";

    Either(Token*) either_token = tokenize(string);
    left_case(either_token);

    if (is_right(either_token)) {
        Token *token = (Token *) either_token.right;
        Node *program_node[256];
        for (int index = 0; index < 256; ++index) program_node[index] = calloc(sizeof(Node), 1);

//        print_token(token);
        Either(Node*[]) either_node_array = parse(token, program_node);
        left_case(either_node_array);

        if (is_right(either_node_array)) {
            Node **node_array = (Node **) either_node_array.right;

//            for (int index = 0; node_array[index] != NULL; ++index) print_node(node_array[index]);

            Either(Signal) either_signal = eval(node_array);
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
