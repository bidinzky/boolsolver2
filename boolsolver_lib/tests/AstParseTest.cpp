//
// Created by Lukas on 19.12.2019.
//

#include "gtest/gtest.h"
#include "AstParse.h"
#include "AstExecute.h"
#include <vector>

using c_str = const char *;

void compare_asts(AST *a1, AST *a2, AST_Registry *reg) {
    auto v1 = TruthTable(a1, reg);
    auto v2 = TruthTable(a2, reg);
    do {
        auto vec1 = v1.exec();
        auto vec2 = v2.exec();
        if (vec1.size() != vec2.size()) {
            ADD_FAILURE() << "size of vectors not equal";
        }
        ASSERT_EQ(vec1[vec1.size() - 1], vec2[vec1.size() - 1]);
        v1.inc();
        v2.inc();
    } while (v1 != v1.end());
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

TEST(AstParse, AND) {
    AST ast = AST();
    AST_Registry reg = AST_Registry();
    AST simple_op = AST();
    c_str s1 = "a&b";

    ast = parse(s1, 3, &reg);
    simple_op.op = AST_OP::AND;
    simple_op.data.emplace_back(&reg['a']);
    simple_op.data.emplace_back(&reg['b']);
    compare_asts(&ast, &simple_op, &reg);
}

TEST(AstParse, OR) {
    AST ast = AST();
    AST_Registry reg = AST_Registry();
    AST simple_op = AST();
    c_str s2 = "a|b";

    ast = parse(s2, 3, &reg);
    simple_op.op = AST_OP::OR;
    simple_op.data.emplace_back(&reg['a']);
    simple_op.data.emplace_back(&reg['b']);
    compare_asts(&ast, &simple_op, &reg);
}

TEST(AstParse, NOT) {
    AST ast = AST();
    AST_Registry reg = AST_Registry();
    AST simple_op = AST();
    c_str s3 = "!a";

    ast = parse(s3, 2, &reg);
    simple_op.op = AST_OP::NOT;
    simple_op.data.emplace_back(&reg['a']);
    compare_asts(&ast, &simple_op, &reg);
}

TEST(AstParse, XOR) {
    AST ast = AST();
    AST_Registry reg = AST_Registry();
    reg.try_emplace('a');
    reg.try_emplace('b');
    reg.try_emplace('c');
    AST simple_op = AST();
    c_str s4 = "a^b";

    ast = parse(s4, 3, &reg);
    simple_op.op = AST_OP::XOR;
    simple_op.data.emplace_back(&reg['a']);
    simple_op.data.emplace_back(&reg['b']);
    compare_asts(&ast, &simple_op, &reg);
}

TEST(AstParse, Complex1) {
    AST ast = AST();
    AST bracket = AST();
    AST_Registry reg = AST_Registry();
    reg.try_emplace('a');
    reg.try_emplace('b');
    reg.try_emplace('c');
    AST simple_op = AST();
    c_str s5 = "a&(b|c)";

    ast = parse(s5, 7, &reg);
    simple_op.op = AST_OP::AND;
    simple_op.data.emplace_back(&reg['a']);
    bracket.op = AST_OP::OR;
    bracket.data.emplace_back(&reg['b']);
    bracket.data.emplace_back(&reg['c']);
    simple_op.data.emplace_back(bracket);
    compare_asts(&ast, &simple_op, &reg);
}

TEST(AstParse, Complex2) {
    AST ast = AST();
    AST bracket = AST();
    AST n = AST();
    AST_Registry reg = AST_Registry();
    reg.try_emplace('a');
    reg.try_emplace('b');
    reg.try_emplace('c');
    AST simple_op = AST();
    c_str s6 = "!(b^!c)";

    ast = parse(s6, 7, &reg);
    simple_op.op = AST_OP::NOT;
    bracket.op = AST_OP::XOR;
    bracket.data.emplace_back(&reg['b']);
    n.op = AST_OP::NOT;
    n.data.emplace_back(&reg['c']);
    bracket.data.emplace_back(n);
    simple_op.data.emplace_back(bracket);
    compare_asts(&ast, &simple_op, &reg);
}

TEST(AstParse, Complex3) {
    AST o = AST();
    AST a = AST();
    AST ast = AST();
    AST_Registry reg = AST_Registry();
    reg.try_emplace('a');
    reg.try_emplace('b');
    reg.try_emplace('c');
    c_str s7 = "a&b|c";

    ast = parse(s7, 5, &reg);
    a.op = AST_OP::AND;
    a.data.emplace_back(&reg['a']);
    a.data.emplace_back(&reg['b']);
    o.op = AST_OP::OR;
    o.data.emplace_back(a);
    o.data.emplace_back(&reg['c']);
    compare_asts(&ast, &o, &reg);
}