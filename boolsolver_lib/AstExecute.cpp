//
// Created by Lukas on 16.12.2019.
//

#include <iostream>
#include <algorithm>
#include "AstExecute.h"

using namespace std;

bool exec(AST *ast) {
    if (ast->op == AST_OP::NOT) {
        return !exec(&ast->data[0]);
    } else {
        vector<bool> t;
        bool tmp = false;
        for (auto i : ast->data) {
            t.push_back(exec(&i));
        }
        switch (ast->op) {
            case AST_OP::AND:
                return all_of(t.begin(), t.end(), [](auto i) { return i; });
            case AST_OP::OR:
                return any_of(t.begin(), t.end(), [](auto i) { return i; });
            case AST_OP::XOR:
                for_each(t.begin(), t.end(), [&tmp](auto i) { tmp = tmp ^ i; });
                return tmp;
            default:
                return false;
        }
    }
}

bool exec(variant<AST, bool *> *var) {
    if (holds_alternative<AST>(*var)) {
        return exec(&get<AST>(*var));
    } else {
        return *get<bool *>(*var);
    }
}

void TruthTable::print(AST *ast, AST_Registry *reg) {
    TruthTable::print(TruthTable(ast, reg));
}

void TruthTable::print(const TruthTable &ttp) {
    auto max_size = ttp.reg->size() * 5 + 6;
    cout << string(max_size, '-') << "\n";
    cout << "|";

    for (auto varname : *ttp.reg) {
        cout << " " << varname.first << " " << "|";
    }
    cout << "| res |\n";
    cout << string(max_size, '-') << "\n";
    for (auto line : ttp) {
        cout << "|";
        for (int i = 0; i < line.size() - 1; i++) {
            cout << " " << line[i] << " " << "|";
        }
        cout << "|  " << line[line.size() - 1] << "  " << "|";
        cout << "\n";
        cout << string(max_size, '-') << "\n";
    }
}

std::vector<bool> TruthTable::exec() const {
    vector<bool> res;
    unsigned long j = this->reg->size() - 1;
    for (auto &r: *this->reg) {
        bool var_state = this->i & (1u << j);
        res.push_back(var_state);
        this->reg->insert_or_assign(r.first, var_state);
        j--;
    }
    res.push_back(::exec(this->ast));
    return res;
}
