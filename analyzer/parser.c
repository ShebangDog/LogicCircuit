//
// Created by ayumu on 2020/06/12.
//

#include "model/token.h"
#include "parser.h"
#include "../utility/converter.h"
#include "../utility/string_util.h"

// <circuit> ::= <signed-signal> (<binary> <signed-signal>)*
// <signed-signal> ::= (<unary>)* <primary>
// <primary> ::= <signal> | "(" <circuit> ")"
//
// <binary> ::= and | or | xor
// <signal> ::= 1 | 0
// <unary> :: = not

Token *head;

Either(Node*) parse(Token *token) {
    head = token;
    return block();
}

unsigned consume_token_parser(char *string);

void expect_token_parser(char *string);

static Either(Node*) block() {
    if (consume_token_parser(ROOT_TOKEN.value)) {
        Either(Node*) result = circuit();
        if (!equal_end_token(*head)) return error_occurred("expected end token");

        return result;
    }

    return error_occurred("error in block");
}

// <circuit> ::= <signed-signal> (<binary> <signed-signal>)*
static Either(Node*) circuit() {
    Either(Node*) either_signed_signal = signed_signal();

    while (1) {
        if (!isbinary_token(*head)) return either_signed_signal;
        else {
            NodeKind kind = token_to_node_kind(*head);
            head = head->next_token;

            if (is_left(either_signed_signal)) return either_signed_signal;
            if (is_right(either_signed_signal)) {
                Either(Node*) right_either_signed_signal = signed_signal();
                if (is_left(right_either_signed_signal)) return right_either_signed_signal;
                if (is_right(right_either_signed_signal)) {
                    either_signed_signal.right = (RIGHT_T *) new_node_binary(
                            kind,
                            (Node *) either_signed_signal.right,
                            (Node *) right_either_signed_signal.right);
                }
            }
        }
    }

}

// <signed-signal> ::= (<unary>)* <primary>
static Either(Node*) signed_signal() {
    if (!isunary_token(*head)) return primary();
    else {
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

    return error_occurred("error at signed_signal");
}

// <primary> ::= <signal> | "(" <circuit> ")"
static Either(Node*) primary() {
    if (consume_token_parser("(")) {
        return ({
            Either(Node*) either = circuit();
            consume_token_parser(")") ? either : error_occurred("expect closing bracket");
        });
    } else {
        return ({
            Either(Node*) either = signal();
            either;
        });
    }
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

    if (!equal_string(head->value, string)) return false;

    *head = *head->next_token;
    return true;
}
