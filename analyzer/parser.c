//
// Created by ayumu on 2020/06/12.
//

#include "model/token.h"
#include "parser.h"
#include "../utility/converter.h"
#include "../utility/string_util.h"

// <program> ::= ( <statement> )*
// <statement> ::= <assignment> ";"
// <assignment> ::= <circuit> ( "=" <circuit> )
//
// <circuit> ::= <signed-signal> (<binary> <signed-signal>)*
// <signed-signal> ::= (<unary>)* <primary>
// <primary> ::= <id> | <signal> | "(" <circuit> ")"
//
// <binary> ::= and | or | xor
// <signal> ::= 1 | 0
// <unary> :: = not
// <id> ::= [a-z]

Token *head;

Either(Node*[]) parse(Token *token, Node *result[]) {
    head = token;
    return program(result);
}

unsigned consume_token_parser(char *string);

void expect_token_parser(char *string);

static Either(Node*[]) program(Node *result[]) {
    if (!consume_token_parser(ROOT_TOKEN.value)) return error_occurred("expected root token but got %s", head->value);

    int index = 0;
    for (;;) {
        if (head == NULL) return error_occurred("expected end token but got NULL");

        if (equal_string(END_TOKEN.value, head->value)) {
            if (!consume_token_parser(END_TOKEN.value))
                return error_occurred("expected end token but got %s", head->value);

            result[index] = NULL;
            return (Either(Node*[])) {.right = (RIGHT_T *) result};
        }

        Either(Node*) either_statement = statement();
        if (is_left(either_statement)) return either_statement;

        Node *statement = (Node *) either_statement.right;

        result[index++] = statement;
    }
}

// <statement> ::= <assignment> ";"
static Either(Node*) statement() {
    Either(Node*) either_assignment = assignment();
    if (is_left(either_assignment)) return either_assignment;

    if (!consume_token_parser(";")) return error_occurred("expected \";\" but got %s", head->value);

    return either_assignment;
}

// <assignment> ::= <circuit> ( "=" <circuit> )
static Either(Node*) assignment() {
    Either(Node*) either_left = circuit();
    if (is_left(either_left)) return either_left;

    Node *left = (Node *) either_left.right;

    if (!consume_token_parser("=")) return (Either(Node*)) {.left = NULL, .right = (RIGHT_T *) left};
    else {
        Either(Node*) either_right = circuit();
        if (is_left(either_right)) return either_right;

        Node *right = (Node *) either_right.right;

        return (Either(Node*)) {.left = NULL, .right = (RIGHT_T *) new_node_assignment(left, right)};
    }
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

        Node *right = (Node *) either_signed_signal.right;

        Either(Node*) either = {.right = (RIGHT_T *) new_node_signed_signal(kind_unary, right)};
        return either;
    }
}

// <primary> ::= <id> | <signal> | "(" <circuit> ")"
static Either(Node*) primary() {
    if (consume_token_parser("(")) {
        return ({
            Either(Node*) either = circuit();
            consume_token_parser(")") ? either : error_occurred("expect \')\' but got %s", head->value);
        });
    }

    if (issignal_token(*head)) return signal();

    if (isid_token(*head)) return id();

    return error_occurred("expected id or signal but got %s", head->value);
}

static Either(Node*) signal() {
    int value = head->value[0] - '0';
    head = head->next_token;

    return (Either(Node*)) {.right = (RIGHT_T *) new_node_signal(value)};
}

static Either(Node*) id() {
    char name = head->value[0];
    head = head->next_token;

    return (Either(Node*)) {.right = (RIGHT_T *) new_node_id(name)};
}

unsigned consume_token_parser(char *string) {

    if (!equal_string(head->value, string)) return false;

    head = head->next_token;
    return true;
}
