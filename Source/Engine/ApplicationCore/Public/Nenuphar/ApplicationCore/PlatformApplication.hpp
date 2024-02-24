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
         * \return Platform pplication single instance.
         */
        static PlatformApplication& GetPlatformApplication();

        /**
         * Application singletion.
         *
         * \brief
         * \return Application single instance.
         */
        static Application& GetApplication();

    private:
        static SharedRef<PlatformApplication> Application;

    };

}
