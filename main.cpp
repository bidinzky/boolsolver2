#include "boolsolver_lib/AstParse.h"
#include "boolsolver_lib/AstExecute.h"
#include <iostream>

int main() {
    AST_Registry reg;
    std::string s;

    while (true) {
        printf("input boolean expression: ");
        getline(std::cin, s);
        if (s.empty()) {
            return 0;

        }
        reg.clear();
        AST a = parse(s.c_str(), &reg);
        TruthTable::print(&a, &reg);
        printf("\n");
    }
}
