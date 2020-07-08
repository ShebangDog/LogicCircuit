cmake_minimum_required(VERSION 3.13)
project(LogicCircuit C)

set(CMAKE_C_STANDARD 11)

add_executable(LogicCircuit main.c analyzer/lexer.h analyzer/model/token.h analyzer/model/token.c analyzer/lexer.c analyzer/model/operator.h utility/debug.c utility/debug.h analyzer/parser.h analyzer/model/operator.c analyzer/model/node.h analyzer/parser.c utility/converter.h utility/converter.c analyzer/model/node.c analyzer/model/signal.c analyzer/evaluator.c utility/string_util.h utility/string_util.c utility/either.h utility/either.c utility/debug.c)