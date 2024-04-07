#pragma once

#include <unordered_map>

#include "Nenuphar/Common/Common.hpp"
#include "Nenuphar/EventSystem/Delegate.hpp"

namespace Nenuphar
{

    template<typename ...Args>
    class Signal
    {
        using Storage = std::unordered_map<
                DelegateTag,
                Delegate<Args...>
                >;

    public:
        void Connect(Delegate<Args...>& delegate);

        void Disconnect(DelegateTag tag);

        void Disconnect(Delegate<Args...> delegate);

        void Emit(Args&&... args);

        Signal() = default;

    private:
        Storage storage{};
    };

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
    void Signal<Args...>::Emit(Args&&... args)
    {
        for (auto& el : storage)
        {
            el.second.GetHandler()(std::forward<Args>(args)...);
        }
    }

    template<typename... Args>
    void Signal<Args...>::Connect(Delegate<Args...>& delegate)
    {
        storage[delegate.GetTag()] = delegate;
    }

}