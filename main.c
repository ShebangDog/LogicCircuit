#include "Analyzer/lexer.h"
#include "Analyzer/parser.h"
#include "Utility/debug.h"

int main(int argc, char *argv[]) {
    tokenize("1 and 1");
    print_token(lexer.token);

    parse(lexer.token);
    print_node(parser.tree);

    return 0;
}

void test_case() {
    "1 1 0 0 or not not not not and xor";
    "1 and 1 or not not not 0 and 1";
    "1 or not not not not not not 1 and 0";
}
