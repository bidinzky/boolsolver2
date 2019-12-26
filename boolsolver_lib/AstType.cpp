//
// Created by Lukas on 23.12.2019.
//

#include "AstType.h"
#include <iostream>
#include <string>
#include <algorithm>

char findVarByValue(AST_Registry* reg, bool* b) {
    for (auto& it : *reg) {
        if(b == &it.second){
            return it.first;
        }
    }
    return '\0';
}

bool operator==(const AST& lhs, const AST& rhs) {
    if(lhs.op != rhs.op) {
        return false;
    }
    if(lhs.data.size() != rhs.data.size()) {
        return false;
    }
    std::vector<int> used_indexi;
    for(auto variant : lhs.data) {
        bool isNotFound = true;
        for(auto v2 : rhs.data) {
            if(variant.index() == v2.index()) {
                if(std::holds_alternative<AST>(variant)) {
                    if(std::get<AST>(variant) == std::get<AST>(v2)) {
                        isNotFound = false;
                        break;
                    }
                }else{
                    if(std::get<bool*>(variant) == std::get<bool*>(v2)) {
                        isNotFound = false;
                        break;
                    }
                }
            }
        }
        if(isNotFound) {
            return false;
        }
    }
    return true;
}

void AST::print(std::ostream& os, bool last) const {
    char op;
    switch (this->op) {
        case AND:
            op = '&';
            break;
        case OR:
            op = '|';
            break;
        case NOT:
            op = '!';
            break;
        case XOR:
            op = '^';
            break;
        default:
            op = '\0';
    }

    for(int i = 0;i<this->data.size();i++) {
        auto val = this->data[i];
        if(std::holds_alternative<AST>(val)){
            os << "(";
            std::get<AST>(val).print(os, false);
            os << ")";
        }else{
            bool* b = std::get<bool*>(val);
            os << findVarByValue(this->reg, b);
        }
        if(i < (this->data.size() - 1)) {
            os << op;
        }
    }

    if(last){
        os << "\n";
    }
}

std::ostream& operator<<(std::ostream& os, AST const& ty) {
    ty.print(os);
    return os;
}



/*void AST::print(std::ostream &os, AST_Registry* reg, bool last) {
    char op;
    switch (this->op) {
        case AND:
            op = '&';
            break;
        case OR:
            op = '|';
            break;
        case NOT:
            op = '!';
            break;
        case XOR:
            op = '^';
            break;
        default:
            op = '\0';
    }

    for(int i = 0;i<this->data.size();i++) {
        auto val = this->data[i];
        if(std::holds_alternative<AST>(val)){
            os << "(";
            std::get<AST>(val).print(os, reg, false);
            os << ")";
        }else{
            bool* b = std::get<bool*>(val);
            os << findVarByValue(reg, b);
        }
        if(i < (this->data.size() - 1)) {
            os << op;
        }
    }
    if(last){
        os << "\n";
    }
}
*/