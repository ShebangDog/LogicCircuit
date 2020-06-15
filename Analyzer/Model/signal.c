//
// Created by twilightskyasterisk on 6/14/20.
//

#include "signal.h"

Signal on = {.value = 1};

Signal off = {.value = 0};

Signal not_signal(Signal signal) {
    return signal.value == 1 ? off : on;
}