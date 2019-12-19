//
// Created by Lukas on 16.12.2019.
//

#ifndef BOOLPARSER_ASTPARSE_H
#define BOOLPARSER_ASTPARSE_H

#include "AstType.h"

AST parse(const char *str, size_t length, AST_Registry *reg);

AST parse(const char *str, AST_Registry *reg);

#endif //BOOLPARSER_ASTPARSE_H
