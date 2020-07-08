//
// Created by ayumu on 2020/06/28.
//
#include <stddef.h>
#include "either.h"

bool is_right(struct Either either) {
    return either.right != NULL;
}

bool is_left(struct Either either) {
    return either.left != NULL;
}

Either(Error) error_occurred(const LEFT_T message) {
    return ({
        Either(Error) either = {.left = message, .right = NULL};
        either;
    });
}

