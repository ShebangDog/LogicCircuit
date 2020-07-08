//
// Created by twilightskyasterisk on 6/16/20.
//

#ifndef LOGICCIRCUIT_EVALUATOR_H
#define LOGICCIRCUIT_EVALUATOR_H

#include "model/signal.h"
#include "model/node.h"
#include "../utility/either.h"

Either(Signal) eval(Node *node);

#endif //LOGICCIRCUIT_EVALUATOR_H
