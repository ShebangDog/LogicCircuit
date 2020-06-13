//
// Created by ayumu on 2020/06/12.
//

#include <string.h>
#include "Model/token.h"
#include "parser.h"
#include "../Utility/converter.h"

// <circuit> ::= <primary> | <primary> <binary> <primary>
// <primary> ::= <signed-signal> | "(" <circuit> ")"
// <signed-signal> ::= <signal> | <unary> <signed-signal>
// <unary> ::= not
// <binary> ::= and | xor | or
// <signal> ::= 1 | 0

void parse(Token *token) {
    parser.tree = circuit(token->nextToken);
    printf("last token is Token(value: %s, kind: %s)\n", token->value, token_kind_name[token->kind]);
}

unsigned consume_token_parser(Token *token, char *string);

void expect_token_parser(Token *token, char *string);

// <circuit> ::= <primary> | <primary> <binary> <circuit>
static Node *circuit(Token *token) {
    puts("circuit");

    if (equal_end_token(*token)) return NULL;

    Node *node = primary(token);

    *token = *token->nextToken;
    if (isbinary_token(*token)) {
        printf("token(value: %s kind: %s)\n", token->value, token_kind_name[token->kind]);
        node = new_node_binary(token_to_node_kind(*token), node, circuit(token->nextToken));
    }

    return node;

}

// <primary> ::= <signed-signal> | "(" <circuit> ")"
static Node *primary(Token *token) {
    puts("primary");
    Node *node;

    if (consume_token_parser(token, "(")) {
        node = circuit(token);
        expect_token_parser(token, ")");
    } else {
        node = signed_signal(token);
    }

    return node;
}

static Node *signed_signal(Token *token) {
    puts("signed-signal");
    Node *node = NULL;

    printf("token(value: %s kind: %s)\n", token->value, token_kind_name[token->kind]);
    if (issignal_token(*token)) {
        puts("issignal");
        return ({
            node = signal(token);
            node;
        });
    }

    if (isunary_token(*token)) {
        puts("isunary");
        return ({
            node = new_node_signed_signal(token_to_node_kind(*token), signed_signal(token->nextToken));

            node;
        });
    }

    puts("signed-signal error");
    exit(1);

}

static Node *signal(Token *token) {
    puts("signal");
    int value = token->value[0] - '0';

    return new_node_signal(value);
}

unsigned equal_parser(char *s1, char *s2, unsigned len) {
    return !strncmp(s1, s2, len);
}

unsigned consume_token_parser(Token *token, char *string) {
    if (!equal_parser(token->value, string, strlen(string))) {
        return false;
    }

    *token = *token->nextToken;
    return true;
}

// if got different value it should display error
void expect_token_parser(Token *token, char *string) {
    if (consume_token_parser(token, string)) return;

    printf("error expect_token_parser / expect [%s] but got [token (value: %s, kind: %s)]\n", string, token->value,
           token_kind_name[token->kind]);
    exit(1);
}