#include "boolsolver_lib/AstParse.h"
#include "boolsolver_lib/AstExecute.h"
#include "boolsolver_lib/AstOptimize.h"
#include <iostream>

int main() {
    AST_Registry reg;
    std::string s = std::string();

    /*while (true) {
        printf("input boolean expression: ");
        getline(std::cin, s);
        if (s.empty()) {
            return 0;

        }
        reg.clear();*/
        s = "(a&b)^(!c|b)";
        reg.emplace('a', false);
        reg.emplace('b', false);
        reg.emplace('c', false);
        AST a = parse(s.c_str(), &reg);
        TruthTable::print(&a, &reg);
        auto res = optimize(&a, &reg);
        TruthTable::print(&res, &reg);
        //TruthTable::print(&a, &reg);
    //}
}
