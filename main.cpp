#include "boolsolver_lib/AstParse.h"
#include "boolsolver_lib/AstExecute.h"
#include "boolsolver_lib/AstOptimize.h"
#include <iostream>

int main() {
    AST_Registry reg;
    std::string s = std::string();

    while (true) {
        printf("input boolean expression: ");
        s.clear();
        getline(std::cin, s);
        if (s.empty()) {
            return 0;

        }
        reg.clear();
        //s = "(a&b)|((!c)^a)";
        AST a = parse(s.c_str(), &reg);
        //auto res = generate_cdnf(&a, &reg);
        TruthTable::print(&a, &reg);
    }
}
