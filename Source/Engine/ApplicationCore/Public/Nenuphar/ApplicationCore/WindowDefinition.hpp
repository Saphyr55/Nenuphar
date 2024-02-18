#pragma once

#include "Nenuphar/Common/Type/Type.hpp"

namespace Nenuphar
{

    struct WindowDefinition
    {
        Float Width;
        Float Height;
        String Title;

        static const WindowDefinition Default;

    };


}