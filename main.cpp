#include "AstParse.h"
#include "AstExecute.h"
#include <iostream>
int main() {
    AST_Registry reg;
    AST a;
    std::string s;

    while(true) {
        getline(std::cin, s);
        parse(s, &a, &reg);
        TruthTable::print_table(&a, &reg);
    }
    /*parse("a&(b^!c)", &a, &reg);
    TruthTable tt = TruthTable(&a, &reg);
    TruthTable::print_table(&a, &reg);
    TruthTable::print_table(tt);

    return 0;*/
}
