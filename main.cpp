#include "AstParse.h"
#include "AstExecute.h"
#include <iostream>

int main() {
    AST_Registry reg;
    AST a;
    std::string s;
    
    while(true) {
        printf("input boolean expression: ");
        std::cin >> s;
        reg.clear();
        a.data.clear();
        parse(s.c_str(), &a, &reg);
        TruthTable::print_table(&a, &reg);
        printf("\n");
    }
    return 0;
}
