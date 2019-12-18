#include "AstParse.h"
#include "AstExecute.h"
#include <iostream>
#include <ncurses.h>

int main() {
    AST_Registry reg;
    AST a = AST();
    std::string s;

    while(true) {
        printf("input boolean expression: ");
        getline(std::cin, s);
        if (s.empty()) {
            return 0;

        }
        reg.clear();
        a.data.clear();
        parse(s.c_str(), &a, &reg);
        TruthTable::print(&a, &reg);
        printf("\n");
    }
}
