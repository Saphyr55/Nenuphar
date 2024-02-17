#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
#include "Nenuphar/Math/Vector4.hpp"

TEST_CASE("Checks whether it gives the right vector on creation.", "[Vector4::Vector4]")
{
    Vector4i defaultVec;
    REQUIRE(defaultVec.x == 0);
    REQUIRE(defaultVec.y == 0);
    REQUIRE(defaultVec.z == 0);
    REQUIRE(defaultVec.w == 0);

    Vector4i vec(5);
    REQUIRE(vec.x == 5);
    REQUIRE(vec.y == 5);
    REQUIRE(vec.z == 5);
    REQUIRE(vec.w == 5);

    Vector4i vec2(0, 1, 2, 3);
    REQUIRE(vec2.x == 0);
    REQUIRE(vec2.y == 1);
    REQUIRE(vec2.z == 2);
    REQUIRE(vec2.w == 3);
}

TEST_CASE("Checks whether it gives the correct number of the vector at a certain index position.", "[Vector4::at]")
{
    Vector4i vec2(0, 1, 2, 3);
    REQUIRE(vec2[0] == 0);
    REQUIRE(vec2[1] == 1);
    REQUIRE(vec2[2] == 2);
    REQUIRE(vec2[3] == 3);
    REQUIRE_THROWS(vec2[4]);
}

TEST_CASE("Compute the euclidean norm.", "[Vector4::Norm]")
{
    REQUIRE_THAT
    (
        Vector4i::Norm(Vector4i(1, 2, 3, 4)),
        Catch::Matchers::WithinRel(5.47722557f, 0.0000001f)
    );
}

TEST_CASE("Normilaze a vector.", "[Vector4::Normalize]")
{
    Vector4i vec(1, 2, 3, 4);
    Vector4f vecN = Vector4i::Normalize(vec);

    REQUIRE_THAT
    (
        vecN.x,
        Catch::Matchers::WithinRel(0.182574f, 0.00001f)
    );
    REQUIRE_THAT
    (
        vecN.y,
        Catch::Matchers::WithinRel(0.365149f, 0.00001f)
    );
    REQUIRE_THAT
    (
        vecN.z,
        Catch::Matchers::WithinRel(0.547723f, 0.00001f)
    );
    REQUIRE_THAT
    (
        vecN.w,
        Catch::Matchers::WithinRel(0.730297f, 0.00001f)
    );
}

TEST_CASE("Checks whether it gives the right vector on addition.", "[Vector4::operator+]")
{
    Vector4i defaultVec(1);
    Vector4i vec(5);
    Vector4i result = defaultVec + vec;

    REQUIRE(result.x == 6);
    REQUIRE(result.y == 6);
    REQUIRE(result.z == 6);
    REQUIRE(result.w == 6);

    Vector4i result2 = defaultVec + 1;
    REQUIRE(result2.x == 2);
    REQUIRE(result2.y == 2);
    REQUIRE(result2.z == 2);
    REQUIRE(result2.w == 2);
}

TEST_CASE("Checks whether it gives the right vector on substration.", "[Vector4::operator-]")
{
    Vector4i defaultVec(5);
    Vector4i vec(1);
    Vector4i result1 = defaultVec - vec;

    REQUIRE(result1.x == 4);
    REQUIRE(result1.y == 4);
    REQUIRE(result1.z == 4);
    REQUIRE(result1.w == 4);

    Vector4i result2 = defaultVec - 5;
    REQUIRE(result2.x == 0);
    REQUIRE(result2.y == 0);
    REQUIRE(result2.z == 0);
    REQUIRE(result2.w == 0);
}

TEST_CASE("Checks whether it gives the right vector on multiplication.", "[Vector4::operator*]")
{
    Vector4i defaultVec(5);
    Vector4i vec(3);

    Vector4i result = defaultVec * vec;
    REQUIRE(result.x == 15);
    REQUIRE(result.y == 15);
    REQUIRE(result.z == 15);
    REQUIRE(result.w == 15);

    Vector4i result2 = defaultVec * 2;
    REQUIRE(result2.x == 10);
    REQUIRE(result2.y == 10);
    REQUIRE(result2.z == 10);
    REQUIRE(result2.w == 10);
}

TEST_CASE("Checks whether it gives the right vector on division.", "[Vector4::operator/]")
{
    Vector4i defaultVec(4);
    Vector4i vec(2);

    Vector4i result = defaultVec / vec;
    REQUIRE(result.x == 2);
    REQUIRE(result.y == 2);
    REQUIRE(result.z == 2);
    REQUIRE(result.w == 2);

    Vector4i result2 = defaultVec / 2;
    REQUIRE(result2.x == 2);
    REQUIRE(result2.y == 2);
    REQUIRE(result2.z == 2);
    REQUIRE(result2.w == 2);
}

TEST_CASE("Checks whether it gives the right vector on dot product.", "[Vector4::Dot]")
{
    Vector4i vec(1, 2, 3, 4);
    Vector4i vec2(4, 3, 2, 1);
    REQUIRE(vec.Dot(vec2) == 20);
}
