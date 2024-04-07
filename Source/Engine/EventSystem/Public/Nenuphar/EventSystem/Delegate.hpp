#pragma once

#include "Nenuphar/Common/Common.hpp"

namespace Nenuphar
{
    
    template<typename ...Args>
    using Handler = std::function<void(Args...)>;

    using DelegateTag = std::size_t;

    template<typename ...Args>
    class Delegate
    {
    public:

        Delegate() = default;

        explicit Delegate(Handler<Args...>&& handler);
        explicit Delegate(const Handler<Args...>& handler);

        const Handler<Args...>& GetHandler() const;
        [[nodiscard]] DelegateTag GetTag() const;

    private:
        DelegateTag m_tag = 0;
        Handler<Args...> m_handler;
    };

    static std::atomic<DelegateTag> LastTag{1};

    template<typename... Args>
    Delegate<Args...>::Delegate(const Handler<Args...>& handler)
            : m_handler(handler)
            , m_tag(LastTag.fetch_add(1))
    {
    }

    template<typename... Args>
    const Handler<Args...>& Delegate<Args...>::GetHandler() const
    {
        return m_handler;
    }

    template<typename ...Args>
    DelegateTag Delegate<Args...>::GetTag() const
    {
        return m_tag;
    }
    
    template<typename ...Args>
    Delegate<Args...>::Delegate(Handler<Args...>&& handler)
            : m_handler(std::forward<Handler<Args...>>(handler))
            , m_tag(LastTag.fetch_add(1))
    {
    }

}
