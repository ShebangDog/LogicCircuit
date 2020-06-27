//
// Created by ayumu on 2020/06/12.
//

#include <string.h>
#include "Model/token.h"
#include "parser.h"
#include "../Utility/converter.h"
#include "../Utility/string_util.h"

// <circuit> ::= <primary> | <primary> <binary> <circuit>
// <primary> ::= <signed-signal> | "(" <circuit> ")"
// <signed-signal> ::= <signal> | <unary> <signed-signal>
// <unary> ::= not
// <binary> ::= and | xor | or
// <signal> ::= 1 | 0

Token *head;

Node* parse(Token *token) {
    head = token;
    return block();
}

unsigned consume_token_parser(char *string);

void expect_token_parser(char *string);

// <block> ::= '{' <circuit> '}'
static Node *block() {
    Node *result;
    if (consume_token_parser(ROOT_TOKEN.value)) {
        result = circuit();
        if (!equal_end_token(*head)) exit(1);

        return result;
    }

    puts("error block");
    exit(1);
}

// <circuit> ::= <primary> | <primary> <binary> <primary>
static Node *circuit() {
    if (equal_end_token(*head)) return NULL;

    Node *node = primary();

    while (1) {
        if (isbinary_token(*head)) {
            NodeKind kind = token_to_node_kind(*head);
            head = head->nextToken;

            node = new_node_binary(kind, node, primary());
        } else {
            return node;
        }
    }

}

// <primary> ::= <signed-signal> | "(" <circuit> ")"
static Node *primary() {
    Node *node;

    if (consume_token_parser("(")) {
        node = circuit();
        expect_token_parser(")");
    } else {
        node = signed_signal();
    }

    return node;
}

static Node *signed_signal() {
    Node *node = NULL;

    if (issignal_token(*head)) {
        return ({
            node = signal();
            node;
        });
    }

    if (isunary_token(*head)) {
        return ({
            NodeKind kind_unary = token_to_node_kind(*head);
            head = head->nextToken;

            node = new_node_signed_signal(kind_unary, signed_signal());
            if (issignal_token(*head)) {
                return ({
                    NodeKind kind_signal = token_to_node_kind(*head);
                    head = head->nextToken;

                    node = new_node_signed_signal(kind_signal, node);
                    node;
                });
            }

            node;
        });
    }

    puts("signed-signal error");
    exit(1);

}

static Node *signal() {
    int value = head->value[0] - '0';
    head = head->nextToken;

    return new_node_signal(value);
}

unsigned consume_token_parser(char *string) {
    if (!equal_substring(head->value, string, strlen(string))) {
        return false;
    }

    *head = *head->nextToken;
    return true;
}

// if got different value it should display error
void expect_token_parser(char *string) {
    if (consume_token_parser(string)) return;

    printf("error expect_token_parser / expect [%s] but got [token (value: %s, kind: %s)]\n", string, head->value,
           token_kind_name[head->kind]);
    exit(1);
}