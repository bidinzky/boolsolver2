//
// Created by Lukas on 19.12.2019.
//
#include <catch2/catch.hpp>
#include "AstParse.h"
#include "AstExecute.h"
#include "AstType.h"


using c_str = const char *;

void compare_asts(AST *a1, AST *a2, AST_Registry *reg) {
    auto v1 = TruthTable(a1, reg);
    auto v2 = TruthTable(a2, reg);
    do {
        auto vec1 = v1.exec();
        auto vec2 = v2.exec();
        REQUIRE(vec1.size() == vec2.size());
        REQUIRE(vec1[vec1.size() - 1] == vec2[vec1.size() - 1]);
        v1.inc();
        v2.inc();
    } while (v1 != v1.end());
}

TEST_CASE("parse AND") {
    AST ast = AST();
    AST_Registry reg = AST_Registry();
    AST simple_op = AST();
    c_str s1 = "a&b";

    ast = parse(s1, 3, &reg);
    simple_op.op = AST_OP::AND;
    simple_op.data.emplace_back(&reg['a']);
    simple_op.data.emplace_back(&reg['b']);
    REQUIRE(ast == simple_op);
    compare_asts(&ast, &simple_op, &reg);
}

TEST_CASE("parse OR") {
    AST ast = AST();
    AST_Registry reg = AST_Registry();
    AST simple_op = AST();
    c_str s2 = "a|b";

    ast = parse(s2, 3, &reg);
    simple_op.op = AST_OP::OR;
    simple_op.data.emplace_back(&reg['a']);
    simple_op.data.emplace_back(&reg['b']);
    REQUIRE(ast == simple_op);
    compare_asts(&ast, &simple_op, &reg);
}

TEST_CASE("parse NOT") {
    AST ast = AST();
    AST_Registry reg = AST_Registry();
    AST simple_op = AST();
    c_str s3 = "!a";

    ast = parse(s3, 2, &reg);
    simple_op.op = AST_OP::NOT;
    simple_op.data.emplace_back(&reg['a']);
    REQUIRE(ast == simple_op);
    compare_asts(&ast, &simple_op, &reg);
}

TEST_CASE("parse XOR") {
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
    REQUIRE(ast == simple_op);
    compare_asts(&ast, &simple_op, &reg);
}

TEST_CASE("parse complex function1") {
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
    REQUIRE(ast == simple_op);
    compare_asts(&ast, &simple_op, &reg);
}

TEST_CASE("parse complex function2") {
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
    REQUIRE(ast == simple_op);
    compare_asts(&ast, &simple_op, &reg);
}

TEST_CASE("parse complex function3") {
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
    CAPTURE(ast);
    REQUIRE(ast == o);
    compare_asts(&ast, &o, &reg);
}