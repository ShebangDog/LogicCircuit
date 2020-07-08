# LogicCircuit

\<circuit\> ::= \<signed-signal\> (\<binary\> \<signed-signal\>)*

\<signed-signal\> ::= (\<unary\>)* \<primary\>

\<primary\> ::= \<signal\> | "(" \<circuit\> ")"

\<binary\> ::= and | or | xor

\<signal\> ::= 1 | 0

\<unary\> :: = not
