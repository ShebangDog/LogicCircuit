//
// Created by twilightskyasterisk on 6/16/20.
//

#ifndef LOGICCIRCUIT_EVALUATOR_H
#define LOGICCIRCUIT_EVALUATOR_H

#include "Model/signal.h"
#include "Model/node.h"

struct {
    Signal signal;
} evaluator;

void eval(Node *node);

#endif //LOGICCIRCUIT_EVALUATOR_H