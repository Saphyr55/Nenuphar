#pragma once

#include "Nenuphar/Common/Common.hpp"

namespace Nenuphar
{

    using DelegateTag = std::size_t;
    static std::atomic<DelegateTag> LastTag{1};

    template<typename ...Args>
    class Delegate
    {
    public:

        Delegate();

        explicit Delegate(Handler<Args...>&& handler);
        explicit Delegate(const Handler<Args...>& handler);

        const Handler<Args...>& GetHandler() const;
        [[nodiscard]] DelegateTag GetTag() const;

        Delegate<Args...>& operator=(Handler<Args...>&&);
        Delegate<Args...>& operator=(const Handler<Args...>&);

    private:
        DelegateTag m_tag = 0;
        Handler<Args...> m_handler;
    };

    template<typename... Args>
    Delegate<Args...>& Delegate<Args...>::operator=(const Handler<Args...>& handler)
    {
        m_handler = handler;
    }

    template<typename... Args>
    Delegate<Args...>& Delegate<Args...>::operator=(Handler<Args...>&& handler)
    {
        m_handler = std::forward<decltype(handler)>(handler);
        return *this;
    }

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

    template<typename... Args>
    Delegate<Args...>::Delegate()
            : m_tag(LastTag.fetch_add(1))
    {

    }

    namespace Service
    {

        template<typename ...Args>
        Delegate<Args...> CreateDelegate(auto h)
        {
            return Delegate<Args...>(Handler<Args...>(h));
        }

        template<typename ...Args>
        Delegate<Args...> CreateDelegate(auto&& func, auto& obj)
        {
            auto handler = std::bind(std::forward<decltype(func)>(func),
                    obj, std::placeholders::_1);
            return Delegate<Args...>(Handler<Args...>(handler));
        }


    }

}
