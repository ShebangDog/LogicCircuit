# LogicCircuit

\<circuit\> ::= \<signed-signal\> | \<signed-signal\> \<binary\> \<signed-signal\>

\<signed-signal\> ::= \<primary\> | \<unary\> \<primary\>

\<primary\> ::= \<signal\> | "(" \<circuit\> ")"

\<binary\> ::= and | or | xor

\<signal\> ::= 1 | 0

\<unary\> :: = not
