#pragma once

#include "Application.hpp"

namespace Nenuphar
{

    class PlatformApplication : public Application
    {
    public:
        /**
         * Platform application singleton.
         *
         * \brief
         * \return
         */
        static PlatformApplication& GetPlatformApplication();

    };

}
