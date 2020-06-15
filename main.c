#include "Analyzer/lexer.h"
#include "Analyzer/parser.h"
#include "Utility/debug.h"

int main(int argc, char *argv[]) {
    tokenize("1 xor 0 or 0 xor 0");
    parse(lexer.token);
    printf("%u\n", eval(parser.tree));

    return 0;
}