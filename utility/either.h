//
// Created by ayumu on 2020/06/28.
//

#ifndef LOGICCIRCUIT_EITHER_H
#define LOGICCIRCUIT_EITHER_H

#include <stdbool.h>

typedef char *LEFT_T;
typedef void *const RIGHT_T;

#define Either(type) struct Either

struct Either {
    LEFT_T left;
    RIGHT_T *right;
};

bool is_right(struct Either either);

bool is_left(struct Either either);

Either(Error) error_occurred(LEFT_T message);

#endif //LOGICCIRCUIT_EITHER_H
