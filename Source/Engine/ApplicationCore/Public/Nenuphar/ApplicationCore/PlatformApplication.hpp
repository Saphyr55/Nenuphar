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
         * \return Platform application single instance.
         */
        static PlatformApplication& GetPlatformApplication();

        /**
         * Application singleton.
         *
         * \brief
         * \return Application single instance.
         */
        static Application& GetApplication();

    private:
        /**
         * Singleton
         */
        static SharedRef<PlatformApplication> Application;

    };

}
