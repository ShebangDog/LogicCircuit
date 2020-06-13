cmake_minimum_required(VERSION 3.16)
project(LogicCircuit C)

set(CMAKE_C_STANDARD 11)

add_executable(LogicCircuit main.c Analyzer/lexer.h Analyzer/Model/token.h Analyzer/Model/token.c Analyzer/lexer.c Analyzer/Model/operator.h Utility/debug.c Utility/debug.h Analyzer/parser.h Analyzer/Model/operator.c Analyzer/Model/node.h Analyzer/parser.c Utility/converter.h Utility/converter.c Analyzer/Model/node.c)