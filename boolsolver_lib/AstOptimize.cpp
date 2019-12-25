//
// Created by Lukas on 20.12.2019.
//

#include "AstOptimize.h"

using namespace std;


int nrOfBitDiff(Minterm const& mt1, Minterm const& mt2) {
    int count = 0;
    for(int i = 0;i<mt1.size();i++){
        if(mt1[i] != mt2[i]) {
            count++;
        }
    }
    return count;
}


Minterm mintermDiff(const Minterm& a, const Minterm& b) {
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

BoolTable createDNFs(TruthTable const& tt) {
    BoolTable bt;
    for(auto i : tt) {
        auto z = i;
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
    return bt;
}

BoolTable createMinTerms(BoolTable const& bt) {
    BoolTable bt2;
    vector<bool> usedMap(bt.size(), false);
    for(int i = 0;i<bt.size();i++) {
        for(int j = i+1;j<bt.size();j++) {
            auto test = nrOfBitDiff(bt[i], bt[j]);
            if(nrOfBitDiff(bt[i], bt[j]) == 1) {
                usedMap[i] = true;
                usedMap[j] = true;

                bt2.emplace_back(mintermDiff(bt[i], bt[j]));
            }
        }
        if(!usedMap[i]) {
            bt2.emplace_back(bt[i]);
        }
    }
    if(bt2.size() < bt.size()) {
        return createMinTerms(bt2);
    }
    return bt2;
}

AST generateAST(BoolTable const& bt, AST_Registry* reg) {
    AST ast(AST_OP::OR);
    for(auto row: bt) {
        AST andAst(AST_OP::AND);
        auto pair = reg->begin();
        for(char i : row){
            if(i <= 1) {
                if(i) {
                    andAst.data.emplace_back(&pair->second);
                }else{
                    andAst.data.emplace_back(AST(AST_OP::NOT, &pair->second));
                }
            }
            pair++;
        }
        ast.data.emplace_back(andAst);
    }
    return ast;
}

AST optimize(TruthTable const& tt) {
    auto dnf = createDNFs(tt);
    auto minterms = createMinTerms(dnf);
    return generateAST(minterms, tt.reg);
}
AST optimize(AST* ast, AST_Registry* reg) {
    return optimize(TruthTable(ast, reg));
}