#include "analyzer/lexer.h"
#include "analyzer/parser.h"
#include "utility/debug.h"
#include "analyzer/evaluator.h"

void left_case(Either(Token | Node | Signal) either);

int main(int argc, char *argv[]) {
    char string[1024] = {0};
    char line[1024] = {0};
    FILE *file = fopen("./../input", "r");
    if (file == NULL) exit(1);

    while (fgets(line, 1024, file) != NULL ) sprintf(string, "%s%s", string, line);

    Either(Token*) either_token = tokenize(string);
    left_case(either_token);

    if (is_right(either_token)) {
        Token *token = (Token *) either_token.right;
        Node program_node[256];
        Node **program_p = (Node **) &program_node;

//        print_token(token);
        Either(Node*[]) either_node_array = parse(token, program_p);
        left_case(either_node_array);

        if (is_right(either_node_array)) {
            Node **node_array = (Node **) either_node_array.right;
            print_nodes(node_array);

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
