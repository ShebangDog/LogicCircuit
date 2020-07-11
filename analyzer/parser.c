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

Either(Node*) parse(Token *token) {
    head = token;
    return block();
}

unsigned consume_token_parser(char *string);

void expect_token_parser(char *string);

static Either(Node*) block() {
    if (consume_token_parser(ROOT_TOKEN.value)) {
        Either(Node*) result = statement();
        if (!equal_end_token(*head)) return error_occurred("expected end token");

        return result;
    }

    return error_occurred("error in block");
}

// <statement> ::= <assignment> ";"
static Either(Node*) statement() {
    Either(Node*) either_assignment = assignment();
    if (is_left(either_assignment)) return either_assignment;

    if (!consume_token_parser(";")) return error_occurred("expected \";\" but got not");

    return either_assignment;
}

// <assignment> ::= <circuit> ( "=" <circuit> )
static Either(Node*) assignment() {
    Either(Node*) either_left = circuit();
    if (is_left(either_left)) return either_left;

    Node *left = (Node *) either_left.right;

    if (!consume_token_parser("=")) return either_left ;
    else {
        Either(Node*) either_right = circuit();
        if (is_left(either_right)) return either_right;

        Node *right = (Node*) either_right.right;

        return ({
            Either(Node*) either = {.left = NULL, .right = (RIGHT_T *) new_node_assignment(left, right)};
            either;
        });
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
        if (is_right(either_signed_signal)) {
            Node *right = (Node *) either_signed_signal.right;

            Either(Node*) either = {.right = (RIGHT_T *) new_node_signed_signal(kind_unary, right)};
            return either;
        }
    }

    return error_occurred("error at signed_signal");
}

// <primary> ::= <id> | <signal> | "(" <circuit> ")"
static Either(Node*) primary() {
    if (consume_token_parser("(")) {
        return ({
            Either(Node*) either = circuit();
            consume_token_parser(")") ? either : error_occurred("expect closing bracket");
        });
    }

    if (issignal_token(*head)) return signal();

    if (isid_token(*head)) return id();

    return error_occurred("unknown error at primary");
}

static Either(Node*) signal() {
    int value = head->value[0] - '0';
    head = head->next_token;

    return ({
        Either(Node*) either = {.right = (RIGHT_T *) new_node_signal(value)};
        either;
    });
}

static Either(Node*) id() {
    char name = head->value[0];
    head = head->next_token;

    return ({
        Either(Node*) either = {.right = (RIGHT_T *) new_node_id(name)};
        either;
    });
}

unsigned consume_token_parser(char *string) {

    if (!equal_string(head->value, string)) return false;

    head = head->next_token;
    return true;
}
