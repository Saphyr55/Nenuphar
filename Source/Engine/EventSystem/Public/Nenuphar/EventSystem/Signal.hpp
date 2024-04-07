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

        void ConnectConn(Handler<ConnectionArgs&, Args...>&& handler);

        Connection<Args...> ConnectHandler(Handler<Args...>&& handler);

        Connection<Args...> Connect(Delegate<Args...>&& delegate);

        Connection<Args...> Connect(Delegate<Args...>& delegate);

        void Disconnect(DelegateTag tag);

        void Disconnect(Delegate<Args...> delegate);

        void Emit(Args... args);

        Signal() = default;

    private:
        Storage m_storage{};
        bool m_isEmit = false;
        std::vector<DelegateTag> m_toRemove;
    };

    template<typename ...Args>
    class Connection
    {
        friend class Signal<Args...>;

    public:
        void Disconnect();

        Connection(DelegateTag delegateTag, Signal<Args...>& signal);

    private:
        DelegateTag m_delegateTag;
        Signal<Args...>& m_signal;
    };

    template<typename... Args>
    void Connection<Args...>::Disconnect()
    {
        m_signal.Disconnect(m_delegateTag);
    }

    template<typename... Args>
    Connection<Args...>::Connection(DelegateTag delegateTag, Signal<Args...>& signal)
        : m_delegateTag(delegateTag), m_signal(signal)
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
        if (!m_isEmit)
        {
            auto it = m_storage.find(tag);
            if (it == m_storage.cend())
            {
                return;
            }
            m_storage.erase(it);
        }
        else
        {
            m_toRemove.push_back(tag);
        }
    }

    template<typename... Args>
    void Signal<Args...>::Emit(Args... args)
    {
        m_isEmit = true;
        for (auto [tag, delegate] : m_storage)
        {
            delegate.GetHandler()(std::forward<Args>(args)...);
        }
        m_isEmit = false;
        for (auto& tagToRemove : m_toRemove)
        {
            Disconnect(tagToRemove);
        }
    }

    template<typename... Args>
    Connection<Args...> Signal<Args...>::ConnectHandler(Handler<Args...>&& handler)
    {
        return Connect(std::move(Delegate<Args...>(std::forward<Handler<Args...>>(handler))));
    }

    template<typename... Args>
    void Signal<Args...>::ConnectConn(Handler<ConnectionArgs&, Args...>&& handler)
    {
        auto delegate = MakeUnique<Delegate<Args...>>();
        auto conn = MakeSharedRef<ConnectionArgs>(delegate->GetTag(), *this);
        (*delegate) = [conn, handler](Args&&... args)
        {
            handler(*conn, std::forward<Args>(args)...);
        };

        m_storage[delegate->GetTag()] = *delegate;
    }

    template<typename... Args>
    Connection<Args...> Signal<Args...>::Connect(Delegate<Args...>&& delegate)
    {
        m_storage[delegate.GetTag()] = std::forward<Delegate<Args...>>(delegate);

        return Connection<Args...>(delegate.GetTag(), *this);
    }

    template<typename... Args>
    Connection<Args...> Signal<Args...>::Connect(Delegate<Args...>& delegate)
    {
        m_storage[delegate.GetTag()] = delegate;

        return Connection<Args...>(delegate.GetTag(), *this);
    }

}