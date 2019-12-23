//
// Created by Lukas on 23.12.2019.
//

#include "AstType.h"
#include <iostream>
#include <string>

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

void print(std::ostream& os, AST const& value, unsigned int offset) {
    os << std::string(offset, '\t');
    os << "AST:\n";
    os << std::string(offset+1, '\t');
    os << "os: ";
    switch (value.op) {
        case AST_OP::AND:
            os << "AND";
            break;
        case AST_OP::OR:
            os << "OR";
            break;
        case AST_OP::NOT:
            os << "NOT";
            break;
        case AST_OP::XOR:
            os << "XOR";
            break;
        default:
            os << "unknown";
    }
    os << "\n";
    os << std::string(offset+1, '\t');
    os << "data:[\n";
    for(auto i : value.data) {
        if(std::holds_alternative<AST>(i)) {
            print(os, std::get<AST>(i), offset + 2);
            os << "\n";
        }else{
            bool* b = std::get<bool*>(i);
            os << std::string(offset+2, '\t');
            os << ((*b)?std::string("true"):std::string("false"));
            os << ",\n";
        }
    }
    os << std::string(offset+1, '\t');
    os << "]";
}

void print(std::ostream& os, AST const& value) {
    print(os,value, 0);
}

std::ostream& operator<<(std::ostream& os, AST const& ty) {
    print(os, ty);
    return os;
}