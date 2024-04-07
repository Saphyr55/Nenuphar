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

TEST_CASE("Check ConnectConn.", "[Signal::ConnectConn]")
{
    Signal<Int> signal;

    signal.ConnectConn([&](auto& conn, Int value)
    {
        REQUIRE(value == 6);
        if (value == 6)
        {
            conn.Disconnect();
        }
    });

    signal.Emit(6);

    signal.Emit(5);
}

TEST_CASE("Check creating delegate with service.", "[Service::CreateDelegate]")
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


class Property : public Signal<Property&>
{
public:
    explicit Property(int value) : m_value(value) { };

    void SetValue(int value);

    [[nodiscard]] int GetValue() const;

private:
    int m_value;
};

void Property::SetValue(int value)
{
    m_value = value;
    Emit(*this);
}

int Property::GetValue() const
{
    return m_value;
}

class PropertyListener
{
public:
    void OnChangedValue(Property& property)
    {
        REQUIRE(property.GetValue() == 2);
    }
};

TEST_CASE("Check delegate with structure and classes.", "[Signal::Signal]")
{
    Property property(3);
    PropertyListener propertyListener;

    auto delegate = Service::CreateDelegate<Property&>(&PropertyListener::OnChangedValue, propertyListener);

    auto connection = property.Connect(delegate);

    property.SetValue(2);

    connection.Disconnect();

    property.ConnectHandler([](Property& property)
    {
        REQUIRE(property.GetValue() == 1);
    });

    property.SetValue(1);
}

