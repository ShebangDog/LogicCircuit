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

Token *head;

void parse(Token *token) {
    head = token->nextToken;
    parser.tree = circuit();
    printf("last token is Token(value: %s, kind: %s)\n", head->value, token_kind_name[head->kind]);
}

unsigned consume_token_parser(char *string);

void expect_token_parser(char *string);

// <circuit> ::= <primary> | <primary> <binary> <circuit>
static Node *circuit() {
    puts("circuit");

    if (equal_end_token(*head)) return NULL;

    Node *node = primary();

    if (isbinary_token(*head)) {
        printf("token(value: %s kind: %s)\n", head->value, token_kind_name[head->kind]);
        NodeKind kind = token_to_node_kind(*head);
        head = head->nextToken;

        node = new_node_binary(kind, node, circuit());
    }

    return node;

}

// <primary> ::= <signed-signal> | "(" <circuit> ")"
static Node *primary() {
    puts("primary");
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
    puts("signed-signal");
    Node *node = NULL;

    printf("token(value: %s kind: %s)\n", head->value, token_kind_name[head->kind]);

    if (issignal_token(*head)) {
        puts("issignal");
        return ({
            node = signal();
            node;
        });
    }

    if (isunary_token(*head)) {
        puts("isunary");
        return ({
            NodeKind kind_unary = token_to_node_kind(*head);
            head = head->nextToken;

            node = new_node_signed_signal(kind_unary, signed_signal());
            if (issignal_token(*head)) {
                puts("issignal");
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
    puts("signal");
    int value = head->value[0] - '0';
    head = head->nextToken;

    return new_node_signal(value);
}

unsigned equal_parser(char *s1, char *s2, unsigned len) {
    return !strncmp(s1, s2, len);
}

unsigned consume_token_parser(char *string) {
    if (!equal_parser(head->value, string, strlen(string))) {
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