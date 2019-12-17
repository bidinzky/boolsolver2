//
// Created by Lukas on 16.12.2019.
//

#include <iostream>
#include "AstExecute.h"

bool exec(AST* ast) {
    bool tmp = false;
    switch(ast->op) {
        case AST_OP::NOT:
            tmp = !exec(&ast->data[0]);;
            break;
        case AST_OP::AND:
            tmp = true;
            for(auto i : ast->data) {
                tmp &= exec(&i);
            }
            break;
        case AST_OP::OR:
            for(auto i : ast->data) {
                tmp |= exec(&i);
            }
            break;
        case AST_OP::XOR:
            for(auto i : ast->data) {
                tmp ^= exec(&i);
            }
            break;
    }
    return tmp;
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
    int j = 0;
    for(auto & r: *this->reg) {
        auto tmp2 = this->reg->size()-j-1;
        bool tmp = this->i & (1<<(this->reg->size()-j-1));
        res.push_back(tmp);
        this->reg->insert_or_assign(r.first, tmp);
        j++;
    }
    res.push_back(exec(this->ast));
    return res;
}

void TruthTable::print_table(const TruthTable &ttp) {
    using namespace std;
    auto max_size = ttp.reg->size() * 5 + 6;
    cout << string(max_size, '-') << "\n";
    cout << "|";
    for(auto varname : *ttp.reg) {
        cout << " " << varname.first << " " << "|";
    }
    cout << "| res |\n";
    cout << string(max_size, '-') << "\n";
    for(auto line : ttp) {
        cout << "|";
        for(int i = 0;i<line.size()-1;i++) {
            cout << " " << line[i] << " " << "|";
        }
        cout << "|  " << line[line.size()-1] << "  " << "|";
        cout << "\n";
        cout << string(max_size, '-') << "\n";
    }
}

void TruthTable::print_table(AST* ast, AST_Registry* reg){
    TruthTable::print_table(TruthTable(ast, reg));
}