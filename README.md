# LogicCircuit

\<program\> ::= ( \<statement\> )*

\<statement\> ::= \<assignment\> ";"

\<assignment\> ::= \<circuit\> ( "=" \<circuit\> )

\<circuit\> ::= \<signed-signal\> ( \<binary\> \<signed-signal\> )*

\<signed-signal\> ::= ( \<unary\> )* \<primary\>

\<primary\> ::= \<id\> | \<signal\> | "(" \<circuit\> ")"

\<binary\> ::= and | or | xor

\<signal\> ::= 1 | 0

\<unary\> :: = not
