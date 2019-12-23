//
// Created by Lukas on 16.12.2019.
//

#include "AstParse.h"

using namespace std;

AST parse(const char *str, size_t length, AST_Registry *reg) {
    bool is_not = false;
    bool is_bracket = false;
    AST ast = AST();
    variant<AST, bool *> ast_data;

    int start_index;
    int stop_index;
    int bracket_count;
    for (int i = 0; i < length; i++) {
        if (str[i] == '\0') {
            break;
        }
        switch (str[i]) {
            case '&':
                ast.op = AST_OP::AND;
                break;
            case '|':
                ast.op = AST_OP::OR;
                break;
            case '^':
                ast.op = AST_OP::XOR;
                break;
            case '!':
                is_not = true;
                break;
            case '(':
                is_bracket = true;
                start_index = i+1;
                stop_index = start_index;
                bracket_count = 1;
                do {
                    if (str[stop_index] == ')') {
                        bracket_count--;
                    } else if (str[stop_index] == '(') {
                        bracket_count++;
                    }
                    stop_index++;
                } while (stop_index < length && str[stop_index] != '\0' && bracket_count > 0);

                ast_data = parse(str + start_index, stop_index - start_index - 1, reg);
                i = stop_index - 2;
                break;
            default:
                if (!is_bracket) {
                    reg->try_emplace(str[i]);
                    ast_data = &reg->at(str[i]);
                }

                if (is_not) {
                    is_not = false;
                    AST a;
                    a.op = AST_OP::NOT;
                    a.data.emplace_back(ast_data);
                    ast_data = a;
                }
                is_bracket = false;
                ast.data.emplace_back(ast_data);
        }
    }
    if (ast.op != AST_OP::NOT && ast.data.size() == 1 && std::holds_alternative<AST>(ast.data[1])) {
        return std::get<AST>(ast.data[0]);
    }
    return ast;
}

AST parse(const char *str, AST_Registry *reg) {
    int i = 0;
    for(;str[i] != '\0'; i++);
    return parse(str, i, reg);
}