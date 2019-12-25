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
class AST {
public:
    AST() = default;;
    explicit AST(AST_OP o): op(o) {}
    AST(AST_OP op, std::variant<AST, bool *> &data) : op(op), data(1, data) {}

    template <typename...Args>
    AST(AST_OP op, Args... args): op(op), data({args...}) {};

    AST_OP op;
    std::vector<std::variant<AST, bool *>> data;
};

bool operator==(const AST& lhs, const AST& rhs);
void print(std::string* s, AST const& value, unsigned int offset);
void print(std::string* s, AST const& value);
std::ostream& operator<<(std::ostream& os, AST const& ty);
#endif //BOOLPARSER_ASTTYPE_H
