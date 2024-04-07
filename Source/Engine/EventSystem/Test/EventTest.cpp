#include <catch2/catch_test_macros.hpp>

#include "Nenuphar/EventSystem/Delegate.hpp"
#include "Nenuphar/EventSystem/Signal.hpp"

using namespace Nenuphar;

TEST_CASE("Check delegate.", "[Delegate::Delegate]")
{

    Handler<const Int&> handler = [](auto& x)
    {
        REQUIRE(x == 5);
    };

    Delegate<const Int&> delegate(handler);

    Delegate<const Int&> delegate2([](auto& x)
    {
        REQUIRE(x == 4);
    });

    Signal<const Int&> signal;

    signal.Connect(delegate);

    signal.Emit(5);

    signal.Disconnect(delegate.GetTag());

    signal.Connect(delegate2);

    signal.Emit(4);

    signal.Disconnect(delegate2);

    signal.Connect(delegate);

    signal.Emit(5);
}