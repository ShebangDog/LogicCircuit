#include "Analyzer/lexer.h"
#include "Analyzer/parser.h"
#include "Analyzer/evaluator.h"

int main(int argc, char *argv[]) {
    tokenize("1 xor 0 or 0 xor 0");
    parse(lexer.token);
    eval(parser.tree);

    printf("%u\n", evaluator.signal.value);

    return 0;
}