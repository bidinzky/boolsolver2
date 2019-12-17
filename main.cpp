#include "AstParse.h"
#include "AstExecute.h"
#include <iostream>
#include <ncurses.h>

int main() {
    AST_Registry reg;
    AST a;
    std::string s;

    while(true) {
        printf("input boolean expression: ");
        getline(std::cin, s);
        reg.clear();
        a.data.clear();
        parse(s, &a, &reg);
        TruthTable::print_table(&a, &reg);
        printf("\n");
    }
    /*parse("a&(b^!c)", &a, &reg);
    TruthTable tt = TruthTable(&a, &reg);
    TruthTable::print_table(&a, &reg);
    TruthTable::print_table(tt);

    return 0;*/
}
