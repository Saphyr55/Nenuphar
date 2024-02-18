#pragma once

#include <cassert>
#include <functional>
#include <map>
#include <type_traits>
#include <typeindex>
#include <any>
#include <forward_list>
#include <stdexcept>

#include "Nenuphar/Common.hpp"
#include "Nenuphar/Core.hpp"

namespace Nenuphar
{

    using EventAddress = String;
    using EventTree = std::map<std::type_index, std::forward_list<std::any>>;
    using EventAddressTree = std::map<EventAddress, EventTree>;

    class EventBus final
    {
    public:
        template<typename E>
        void Connect(StringView address, std::function<void(E&)> handler);

        template<typename E>
        void Emit(StringView address, E& event);

    private:
        EventAddressTree registry;
    };

	template<typename E>
    void EventBus::Connect(const StringView address, std::function<void(E&)> handler)
    {
        registry[address.data()][typeid(E)].emplace_front(handler);
    }

	template<typename E>
    void EventBus::Emit(const StringView address, E& event)
    {
        for (auto const& h : registry[address.data()][typeid(E)])
        {
            if (std::type_index(h.type()) == std::type_index(typeid(std::function<void(E&)>)))
            {
                std::any_cast<std::function<void(E&)>>(h)(event);
            }
            else
            {   
                NP_ERROR("Error EventBus Emission for address the '{}'", address);
                throw std::exception();
            }
        }
    }
    
}

#define NP_EMIT_EVENT(Name, Type, addr) \
		void Emit##Name(::Nenuphar::EventBus& eventBus, const Type& event) const \
        { \
			eventBus.Emit<const Type>(addr, event); \
		}

#define NP_CONNECT_EVENT(Name, Type, addr) \
		void Name(::Nenuphar::EventBus& eventBus, std::function<void(const Type&)>&& h) const \
        { \
			eventBus.Connect<const Type>(addr, h); \
		}

#define NPSignal(Name, Type, addr) \
		NP_EMIT_EVENT(Name, Type, addr) \
		NP_CONNECT_EVENT(Name, Type, addr)

