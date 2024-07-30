#pragma once

#include <typeindex>
#include <any>

#include "Nenuphar/Core/Core.hpp"

namespace Nenuphar
{

    /**
     * Represent the component type.
     */
    using ComponentTI = std::type_index;

    /**
     *
     */
    struct ComponentTIBinding
    {
        Word Row;
    };

    /**
     * Get the component index from the component template type C.
     *
     * @tparam C
     * @return
     */
    template<typename C>
    ComponentTI GetComponentTI()
    {
        return typeid(C);
    }

}
