#include "Nenuphar/Model/Obj/WavefrontObjLexer.hpp"
#include "Nenuphar/Core/Logger/Logger.hpp"
#include <catch2/catch_test_macros.hpp>

using namespace Nenuphar;

TEST_CASE("Obj file lexing test.", "[WavefrontObjLexer::Scan]")
{
    auto source = R"(
        # A 2 x 2 square mapped with a 1 x 1 square
        # texture stretched to fit the square exactly.
        mtllib master.mtl
        v  0.000000 2.000000 0.000000
        v  0.000000 0.000000 0.000000
        v  2.000000 0.000000 0.000000
        v  2.000000 2.000000 0.000000
        vt 0.000000 1.000000
        vt 0.000000 0.000000
        vt 1.000000 0.000000
        vt 1.000000 1.000000
        # 4 vertices
        usemtl wood
        # The first number is the point, then the slash, and the second is the texture point
        f 1/1 2/2 3/3 4/4
        # 1 element
        )";

    
    WavefrontObjLexer lexer;

    auto tokens = lexer.Scan(source);

    REQUIRE(tokens[3].Text == "mtllib");
    REQUIRE(tokens[3].Kind == WavefrontObjToken::Type::MaterialLib);

    REQUIRE(tokens[10].Text == "2.000000");
    REQUIRE(tokens[10].Kind == WavefrontObjToken::Type::Float);
}