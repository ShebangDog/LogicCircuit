//
// Created by ayumu on 2020/06/12.
//

#include "converter.h"
#include "string_util.h"
#include <string.h>

NodeKind token_to_node_kind(Token token) {
    if (token.kind == T_ROOT) return ND_ROOT;
    if (token.kind == T_END) return ND_END;

    if (token.kind == T_SIGNAL) return token.value[0] == '1' ? ND_SIGNAL_ON : ND_SIGNAL_OFF;
    if (token.kind == T_BRACKET) return token.value[0] == '(' ? ND_OPENING_BRACKET : ND_CLOSING_BRACKET;
    if (token.kind == T_ID) return ND_ID;
    if (token.kind == T_EQUAL) return ND_ASSIGNMENT;
    if (token.kind == T_OPERATOR) {
        char *p = token.value;

        for (int i = binary_start; i < binary_end + 1; ++i) {
            if (!equal_substring(binary_name[i], p, strlen(binary_name[i]))) continue;

            if (i == and) return ND_AND;
            if (i == or) return ND_OR;
            if (i == xor) return ND_XOR;

            puts("error token_to_node_kind binary");
            exit(1);
        }

        for (int i = unary_start; i < unary_end + 1; ++i) {
            if (!equal_substring(unary_name[i], p, strlen(unary_name[i]))) continue;

            if (i == not) return ND_NOT;

            puts("error token_to_node_kind unary");
            exit(1);
        }

        printf("error token_to_node_kind / token: {value: %s kind: %s}\n", token.value, token_kind_name[token.kind]);
        exit(1);
    }

    printf("error token_to_node_kind / token: {value: %s kind: %s}\n", token.value, token_kind_name[token.kind]);
    exit(1);
}

Signal char_to_signal(char ch) {
    return ({
        Signal result = {.value = ch - '0'};

        result;
    });
}