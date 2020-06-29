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

Either(Node*) parse(Token *token) {
    head = token;
    return block();
}

unsigned consume_token_parser(char *string);

void expect_token_parser(char *string);

// <block> ::= '{' <circuit> '}'
static Either(Node*) block() {
    if (consume_token_parser(ROOT_TOKEN.value)) {
        Either(Node*) result = circuit();
        if (!equal_end_token(*head)) return error_occurred("expected end token");

        return result;
    }

    return error_occurred("error in block");
}

// <circuit> ::= <primary> | <primary> <binary> <primary>
static Either(Node*) circuit() {
    //if (equal_end_token(*head)) return NULL;

    Either(Node*) either_primary = primary();

    while (1) {
        if (!isbinary_token(*head)) return either_primary;
        else {
            NodeKind kind = token_to_node_kind(*head);
            head = head->next_token;

            if (is_left(either_primary)) return either_primary;
            if (is_right(either_primary)) {
                Either(Node*) right_either_primary = primary();
                if (is_left(right_either_primary)) return right_either_primary;
                if (is_right(right_either_primary)) {
                    either_primary.right = (RIGHT_T *) new_node_binary(
                            kind,
                            (Node *) either_primary.right,
                            (Node *) right_either_primary.right);
                }
            }
        }
    }

}

// <primary> ::= <signed-signal> | "(" <circuit> ")"
static Either(Node*) primary() {
    if (consume_token_parser("(")) {
        return ({
            Either(Node*) either = circuit();
            consume_token_parser(")") ? either : error_occurred("expect closing bracket");
        });
    } else {
        return ({
            Either(Node*) either = signed_signal();
            either;
        });
    }
}

static Either(Node*) signed_signal() {
    if (issignal_token(*head)) {
        return ({
            Either(Node*) either = signal();
            either;
        });
    }

    if (isunary_token(*head)) {
        NodeKind kind_unary = token_to_node_kind(*head);
        head = head->next_token;

        Either(Node*) either_signed_signal = signed_signal();
        if (is_left(either_signed_signal)) return either_signed_signal;
        if (is_right(either_signed_signal)) {
            Node *right = (Node *) either_signed_signal.right;

            Either(Node*) either = {.right = (RIGHT_T *) new_node_signed_signal(kind_unary, right)};
            return either;
        }
    }

    return error_occurred("expect token that is unary or signal");
}

static Either(Node*) signal() {
    int value = head->value[0] - '0';
    head = head->next_token;

    return ({
        Either(Node*) either = {.right = (RIGHT_T *) new_node_signal(value)};
        either;
    });
}

unsigned consume_token_parser(char *string) {
    if (!equal_substring(head->value, string, strlen(string))) {
        return false;
    }

    *head = *head->next_token;
    return true;
}