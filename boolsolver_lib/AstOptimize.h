//
// Created by Lukas on 20.12.2019.
//

#ifndef BOOLPARSER_ASTOPTIMIZE_H
#define BOOLPARSER_ASTOPTIMIZE_H

#include "AstType.h"
#include "AstExecute.h"
#include <vector>



using Minterm = std::vector<char>;
using BoolTable = std::vector<Minterm>; //0,1, all else is dont care


AST optimize(TruthTable const& tt);
AST optimize(AST* ast, AST_Registry* reg);


#endif //BOOLPARSER_ASTOPTIMIZE_H
