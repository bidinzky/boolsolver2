//
// Created by Lukas on 20.12.2019.
//

#ifndef BOOLPARSER_ASTOPTIMIZE_H
#define BOOLPARSER_ASTOPTIMIZE_H

#include "AstType.h"
#include "AstExecute.h"
#include <vector>
#include <variant>
#include <algorithm>

using namespace std;

struct NOTHING_MARKER {};

using variant_ty = variant<AST, bool *, NOTHING_MARKER>;

typedef struct optimizerAst {
    AST_OP op;
    vector<variant_ty> data;
} Optimizer_AST;

int nr_of_ones(optimizerAst op_ast) {
    return count_if(op_ast.data.begin(), op_ast.data.end(), [](const variant_ty& i) {
        return holds_alternative<bool*>(i);
    });
}

vector<optimizerAst> generate_minterms(vector<optimizerAst> va) {
    stable_sort(va.begin(), va.end(), [](const optimizerAst& i, const optimizerAst& j) {
        return nr_of_ones(i) == nr_of_ones(j);
    });
    for(int i = 0;i<va.size();i++) {

    }
    return va;
}
vector<optimizerAst> generate_minterms(vector<AST> va) {
    vector<optimizerAst> op_ast;
    for(auto & i : va) {
        optimizerAst op_ast_loop = optimizerAst();
        op_ast_loop.op = i.op;
        for(auto & j : i.data) {
            if(holds_alternative<AST>(j)) {
                op_ast_loop.data.emplace_back(get<AST>(j));
            }else{
                op_ast_loop.data.emplace_back(get<bool*>(j));
            }
        }
        op_ast.emplace_back(op_ast_loop);
    }
    return generate_minterms(op_ast);
}
vector<AST> generate_cdnf(TruthTable tt) {
    vector<AST> v;
    vector<bool*> vars;
    for(auto i : *tt.reg) {
        vars.emplace_back(&i.second);
    }
    for(vector<bool> i : tt){
        AST res = AST();
        res.op = AST_OP::AND;
        if(i.back() == true) {
            for(int j = 0;j<i.size()-1;j++) {
                if(!i[j]) {
                    AST a = AST();
                    a.op = AST_OP::NOT;
                    a.data.emplace_back(vars[j]);
                    res.data.emplace_back(a);
                }else{
                    res.data.emplace_back(vars[j]);
                }
            }
            v.emplace_back(res);
        }
    }
    auto z = generate_minterms(v);
    return v;
}
vector<AST> generate_cdnf(AST* ast, AST_Registry* reg) {
    return generate_cdnf(TruthTable(ast, reg));
}

#endif //BOOLPARSER_ASTOPTIMIZE_H
