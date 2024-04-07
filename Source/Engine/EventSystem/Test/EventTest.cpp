#include <catch2/catch_test_macros.hpp>

#include "Nenuphar/EventSystem/Delegate.hpp"
#include "Nenuphar/EventSystem/Signal.hpp"

using namespace Nenuphar;

void Foo(const int& x)
{
    REQUIRE(x == 3);
}

TEST_CASE("Check delegate.", "[Delegate::Delegate]")
{

    Signal<const Int&> signal;

    Handler<const Int&> handler = [](auto& x)
    {
        REQUIRE(x == 5);
    };

    Delegate<const Int&> delegate(handler);

    Delegate<const Int&> delegate2([](auto& x)
    {
        REQUIRE(x == 4);
    });

    auto connection = signal.Connect(delegate);
    signal.Emit(5);

    connection.Disconnect();
    signal.Connect(delegate2);
    signal.Emit(4);

    signal.Disconnect(delegate2);
    signal.Connect(delegate);
    signal.Emit(5);

}


TEST_CASE("Check delegate.", "[Service::CreateDelegate]")
{
    Signal<const Int&> signal;

    const Int x = 3;

    auto delegate = Service::CreateDelegate<const Int&>(&Foo);
    Delegate<const Int&> delegate2([](auto& x){ REQUIRE(x == 4); });

    auto connection = signal.Connect(delegate);
    signal.Emit(x);
    connection.Disconnect();
    signal.Connect(delegate2);
    signal.Emit(4);

}
