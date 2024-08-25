#include <catch2/catch_test_macros.hpp>

#include "Nenuphar/Common/Type/Result.hpp"

using namespace Nenuphar;


TEST_CASE("Result constructor.", "[Engine.Common::Result]")
{
    using Err = std::string;
    using Info = std::string;

    Result<Info, Err> r(Result<Info, Err>::kErrTag, "");
}
