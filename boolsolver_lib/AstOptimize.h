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


using Minterm = vector<char>;
using BoolTable = vector<Minterm>; //0,1, all else is dont care
struct MintermOnes {
    int ones;
    int dont_care;
};

MintermOnes nr_ones(Minterm const& mt) {
    MintermOnes mto = MintermOnes();
    for(char i : mt) {
        if(i == 1) {
            mto.ones++;
        }else if(i != 0) {
            mto.dont_care++;
        }
    }
    return mto;
}

bool equal_nr_ones(Minterm const& mt1,Minterm const& mt2) {
    int nr_diff = 0;
    for(int i = 0;i<mt1.size();i++) {
        if(mt1[i] != mt2[i]) {
            if(mt1[i] != 0 && mt2[i] != 0) {

            }
        }
    }
    auto nr_mt1 = nr_ones(mt1);
    auto nr_mt2 = nr_ones(mt2);

    if(nr_mt1.ones > nr_mt2.ones) {
        return (nr_mt1.ones - nr_mt2.ones - nr_mt2.dont_care) <= 1;
    }else{
        return (nr_mt2.ones - nr_mt1.ones - nr_mt1.dont_care) <= 1;
    }
}
Minterm minterm_diff(const Minterm& a, const Minterm& b) {
    Minterm min;
    for(int i = 0;i<a.size();i++) {
        if(a[i] != b[i]) {
            if(a[i] != 0 && b[i] != 0) {
                min.emplace_back(1);
            }else if(a[i] != 1 && b[i] != 1) {
                min.emplace_back(0);
            }else if(a[i] <= 1 && b[i] <= 1) {
                min.emplace_back(2);
            }else{
                throw "error";
            }
        }else{
            min.emplace_back(a[i]);
        }
    }
    return min;
}

BoolTable optimize(BoolTable& bt) {
    BoolTable bt2;
    for(int i = 0;i<bt.size();i++) {
        for(int j = i+1;j<bt.size();j++) {
            if(bt[i] != bt[j]) {
                if(equal_nr_ones(bt[i], bt[j])) {
                    bt2.emplace_back(minterm_diff(bt[i],bt[j]));
                }
            }
        }
    }
    return bt2;
}
BoolTable optimize(TruthTable const& tt) {
    BoolTable bt;
    for(auto i : tt) {
        if(i[i.size()-1]) {
            //wenn true
            i.pop_back(); //remove function value --> ist immer true;
            Minterm vc;
            for(auto j : i){
                vc.emplace_back(j);
            }
            bt.emplace_back(vc);
        }
    }
    return optimize(bt);
}
BoolTable optimize(AST* ast, AST_Registry* reg) {
    return optimize(TruthTable(ast, reg));
}

/*typedef struct optimizerAst {
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
}*/

#endif //BOOLPARSER_ASTOPTIMIZE_H
