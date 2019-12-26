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
    TruthTable(AST *ast) : ast(ast), i(0) {}

    TruthTable(AST *ast, unsigned int i) :  ast(ast), i(i) {}

    [[nodiscard]] TruthTable begin() const {
        return TruthTable(this->ast, 0);
    }

    [[nodiscard]] TruthTable end() const {
        return TruthTable(this->ast, (1u << this->ast->reg->size()));
    }

    bool operator!=(TruthTable const &other) const {
        return this->i != other.i;
    }

    [[nodiscard]] std::vector<bool> exec() const;

    std::vector<bool> operator*() {
        return this->exec();
    }

    TruthTable const &operator++() {
        this->i++;
        return *this;
    }

    void inc() {
        this->i++;
    }

    static void print(AST *ast);

    static void print(const TruthTable &ttp);

    AST *ast;
private:
    unsigned int i;
};


#endif //BOOLPARSER_ASTEXECUTE_H
