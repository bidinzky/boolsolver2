//
// Created by Lukas on 16.12.2019.
//

#ifndef BOOLPARSER_ASTPARSE_H
#define BOOLPARSER_ASTPARSE_H

#include "AstType.h"
void parse(const char* str, size_t str_len, AST* ast, AST_Registry* reg);
void parse(const char* str, AST* ast, AST_Registry* reg);

#endif //BOOLPARSER_ASTPARSE_H
