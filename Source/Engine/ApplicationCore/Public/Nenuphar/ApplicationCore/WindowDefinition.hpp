#pragma once

#include "Nenuphar/Common/Type/Type.hpp"

namespace Nenuphar
{

    struct WindowDefinition
    {
        Float Width;
        Float Height;
        String Title;
    };

    const WindowDefinition GDefaultWindowDefinition
    {
        .Width = 1080,
        .Height = 720,
        .Title = "Nenuphar.Window",
    };


}