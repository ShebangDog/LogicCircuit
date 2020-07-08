//
// Created by ayumu on 2020/06/12.
//

#ifndef LOGICCIRCUIT_CONVERTER_H
#define LOGICCIRCUIT_CONVERTER_H

#include "../analyzer/model/node.h"
#include "../analyzer/model/token.h"

NodeKind token_to_node_kind(Token token);

Signal char_to_signal(char ch);

#endif //LOGICCIRCUIT_CONVERTER_H
