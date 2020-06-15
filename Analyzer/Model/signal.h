//
// Created by twilightskyasterisk on 6/14/20.
//

#ifndef LOGICCIRCUIT_SIGNAL_H
#define LOGICCIRCUIT_SIGNAL_H

typedef struct {
    unsigned value;
} Signal;

Signal on;

Signal off;

Signal not_signal(Signal signal);

#endif //LOGICCIRCUIT_SIGNAL_H
