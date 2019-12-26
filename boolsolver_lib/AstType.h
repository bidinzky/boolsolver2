//
// Created by Lukas on 16.12.2019.
//

#ifndef BOOLPARSER_ASTTYPE_H
#define BOOLPARSER_ASTTYPE_H

#include <vector>
#include <variant>
#include <unordered_map>

enum AST_OP {
    AND,OR,XOR,NOT
};

using AST_Registry = std::unordered_map<char, bool>;
typedef struct AST {
    AST_OP op;
    std::vector<std::variant<AST, bool *>> data;
    AST_Registry* reg;
    void print(std::ostream& os, bool last = true) const;
} AST;

bool operator==(const AST& lhs, const AST& rhs);
std::ostream& operator<<(std::ostream& os, AST const& ty);
#endif //BOOLPARSER_ASTTYPE_H
