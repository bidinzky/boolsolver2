//
// Created by Lukas on 16.12.2019.
//

#ifndef BOOLPARSER_ASTEXECUTE_H
#define BOOLPARSER_ASTEXECUTE_H

#include "AstType.h"

bool exec(AST* ast);
bool exec(std::variant<AST, bool*>* var);

class TruthTable {
public:
    TruthTable(AST *ast, AST_Registry *reg) : reg(reg), ast(ast), i(0) {}

    TruthTable(AST *ast, AST_Registry *reg, unsigned int i) : reg(reg), ast(ast), i(i) {}

    [[nodiscard]] TruthTable begin() const {
        return TruthTable(this->ast, this->reg, 0);
    }

    [[nodiscard]] TruthTable end() const {
        return TruthTable(this->ast, this->reg, (1u << this->reg->size()));
    }

    bool operator!=(TruthTable const &other) const {
        return this->i != other.i;
    }

    std::vector<bool> operator*() const;

    TruthTable const &operator++() {
        this->i++;
        return *this;
    }

    static void print(AST *ast, AST_Registry *reg);

    static void print(const TruthTable &ttp);

private:
    AST *ast;
    AST_Registry *reg;
    unsigned int i;
};

#endif //BOOLPARSER_ASTEXECUTE_H
