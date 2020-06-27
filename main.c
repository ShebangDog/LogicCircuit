#include "Analyzer/lexer.h"
#include "Analyzer/parser.h"
#include "Analyzer/evaluator.h"
#include "Utility/debug.h"

int main(int argc, char *argv[]) {
    //tokenize("1 xor not not 1 or 1");
    //tokenize("1 or 0 and 0");
    //tokenize("1 and 0 or 1");

    Token *token = tokenize("not 1 xor (1 or 1)");
    print_token(token);

    Node *node = parse(token);
    print_node(node);

    eval(node);

    printf("%u\n", evaluator.signal.value);

    return 0;
}