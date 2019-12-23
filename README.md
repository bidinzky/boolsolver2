# boolsolver2

## Goals
- [ ] calculate the truthtable of a given boolean function
    - [x] AND
    - [x] NOT
    - [x] OR
    - [x] XOR
    - [x] Brackets
    - [ ] Precedence rules (https://stackoverflow.com/questions/47847941/what-is-the-operator-precedence-in-boolean-algebra)
- [ ] minimize the given function 
- [ ] create circuit diagramm

## Usage
At the moment just start the executable and input the boolean function.

Operation | Syntax
---------|--------
NOT a|!a
a AND b|a&b
a OR b|a\|b
a XOR b|a^b
a AND (b XOR c)|a&(b^c)

The output is the truth table of the given function.
