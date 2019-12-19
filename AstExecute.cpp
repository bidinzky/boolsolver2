//
// Created by Lukas on 16.12.2019.
//

#include <iostream>
#include "AstExecute.h"

bool exec(AST* ast) {
    if (ast->op == AST_OP::NOT) {
        return !exec(&ast->data[0]);
    } else if (ast->op == AST_OP::AND) {
        for (auto i : ast->data) {
            if (!exec(&i)) {
                return false;
            }
        }
        return true;
    } else {
        //OR or XOR
        bool tmp = false;
        for (auto i : ast->data) {
            if (exec(&i)) {
                if (ast->op == AST_OP::OR) {
                    return true;
                } else {
                    tmp = !tmp;
                }
            }
        }
        return tmp;
    }
}

bool exec(std::variant<AST, bool*>* var) {
    if(std::holds_alternative<AST>(*var)) {
        return exec(&std::get<AST>(*var));
    }else{
        return *std::get<bool*>(*var);
    }
}

std::vector<bool> TruthTable::operator*() const {
    std::vector<bool> res;
    unsigned long j = this->reg->size() - 1;
    for (auto &r: *this->reg) {
        bool var_state = this->i & (1u << j);
        res.push_back(var_state);
        this->reg->insert_or_assign(r.first, var_state);
        j--;
    }
    res.push_back(exec(this->ast));
    return res;
}

void TruthTable::print(AST *ast, AST_Registry *reg) {
    TruthTable::print(TruthTable(ast, reg));
}

void TruthTable::print(const TruthTable &ttp) {
    using namespace std;
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
