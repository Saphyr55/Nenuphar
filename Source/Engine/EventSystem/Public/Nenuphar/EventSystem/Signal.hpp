#pragma once

#include <unordered_map>

#include "Nenuphar/Common/Common.hpp"
#include "Nenuphar/EventSystem/Delegate.hpp"

namespace Nenuphar
{

    template<typename ...Args>
    class Connection;

    template<typename ...Args>
    class Signal
    {

        using ConnectionArgs = Connection<Args...>;
        using Storage = std::unordered_map<
                DelegateTag,
                Delegate<Args...>
                >;

    public:

        Connection<Args...> ConnectConn(Handler<ConnectionArgs&, Args...>&& handler);

        Connection<Args...> ConnectHandler(Handler<Args...>&& handler);

        Connection<Args...> Connect(Delegate<Args...>&& delegate);

        Connection<Args...> Connect(Delegate<Args...>& delegate);

        void Disconnect(DelegateTag tag);

        void Disconnect(Delegate<Args...> delegate);

        void Emit(Args... args);

        Signal() = default;


    private:
        Storage storage{};

    };

    template<typename ...Args>
    class Connection
    {
        friend class Signal<Args...>;

    public:
        void Disconnect();

    private:
        Connection(Delegate<Args...>& delegate, Signal<Args...>& signal);

    private:
        Delegate<Args...>& m_delegate;
        Signal<Args...>& m_signal;
    };

    template<typename... Args>
    void Connection<Args...>::Disconnect()
    {
        m_signal.Disconnect(m_delegate);
    }

    template<typename... Args>
    Connection<Args...>::Connection(Delegate<Args...>& delegate, Signal<Args...>& signal)
        : m_delegate(delegate), m_signal(signal)
    {
    }

    template<typename... Args>
    void Signal<Args...>::Disconnect(Delegate<Args...> delegate)
    {
        Disconnect(delegate.GetTag());
    }

    template<typename... Args>
    void Signal<Args...>::Disconnect(DelegateTag tag)
    {
        storage.erase(tag);
    }

    template<typename... Args>
    void Signal<Args...>::Emit(Args... args)
    {
        for (auto& el : storage)
        {
            el.second.GetHandler()(std::forward<Args>(args)...);
        }
    }

    template<typename... Args>
    Connection<Args...> Signal<Args...>::ConnectHandler(Handler<Args...>&& handler)
    {
        return Connect(std::move(Delegate<Args...>(std::forward<Handler<Args...>>(handler))));
    }

    template<typename... Args>
    Connection<Args...> Signal<Args...>::ConnectConn(Handler<ConnectionArgs&, Args...>&& handler)
    {
        Delegate<Args...> delegate;
        Connection<Args...> connection(delegate, *this);
        delegate = [&connection, &handler](auto&& ...args)
        {
            handler(connection, std::forward<Args>(args)...);
        };

        storage[delegate.GetTag()] = delegate;

        return connection;
    }

    template<typename... Args>
    Connection<Args...> Signal<Args...>::Connect(Delegate<Args...>&& delegate)
    {
        storage[delegate.GetTag()] = std::forward<Delegate<Args...>>(delegate);

        return Connection<Args...>(delegate, *this);
    }

    template<typename... Args>
    Connection<Args...> Signal<Args...>::Connect(Delegate<Args...>& delegate)
    {
        storage[delegate.GetTag()] = delegate;

        return Connection<Args...>(delegate, *this);
    }

}