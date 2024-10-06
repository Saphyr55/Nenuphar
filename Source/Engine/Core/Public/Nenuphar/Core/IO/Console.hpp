#pragma once

#include "Nenuphar/Common/Type/Type.hpp"

#include <string>

namespace Nenuphar
{

    class Console
    {
    public:
        virtual void WriteMessage(std::string message) = 0;
    };

}// namespace Nenuphar