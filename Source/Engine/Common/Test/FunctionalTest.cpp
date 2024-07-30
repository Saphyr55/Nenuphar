#include <catch2/catch_test_macros.hpp>

#include "Nenuphar/Common/Functional.hpp"

using namespace Nenuphar;

static int Compute(const int x, const int y)
{
	return x + y;
}

TEST_CASE("Partial function.", "[Engine.Common::Partial]") 
{
	auto computePrime = Partial(Compute, 6);

	REQUIRE(computePrime(4) == 10);
	REQUIRE(computePrime(9) != 0);
}

TEST_CASE("Compose function.", "[Engine.Common::Compose]") 
{
	auto lambda1 = [](const int x)
	{
		return x + 1;
	};

	auto lambda2 = [](const int x)
	{
		return x + 1;
	};

	auto computePrime = Compose(lambda1, lambda2);

	REQUIRE(computePrime(2) == 4);
	REQUIRE(computePrime(0) != 0);
}
