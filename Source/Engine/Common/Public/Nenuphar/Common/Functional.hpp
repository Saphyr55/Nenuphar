#pragma once

#ifndef NENUPHAR_FUNCTIONAL_HPP
#define NENUPHAR_FUNCTIONAL_HPP

#include <functional>

namespace Nenuphar
{

	constexpr auto Partial(auto&& f, auto&& ...args)
	{
		return [&f, &args...]<typename... T0>(T0&&... lambdaArgs)
		{
			return f
			(
				std::forward<T0>(lambdaArgs)...,
				std::forward<decltype(args)>(args)...
			);
		};
	}

	constexpr auto Compose(auto&& f1, auto&& f2)
	{
		return [&f1, &f2](auto&& arg)
		{
			return f1(f2(arg));
		};
	}

}

#endif
