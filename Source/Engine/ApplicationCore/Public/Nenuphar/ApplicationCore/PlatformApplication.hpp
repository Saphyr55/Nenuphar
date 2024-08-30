#pragma once

#include "Application.hpp"

namespace Nenuphar
{

    class PlatformApplication : public Application
    {
    public:

        /**
         * @brief Get the Platform Application singleton instance.
         * 
         * @return PlatformApplication& 
         */
        static PlatformApplication& GetPlatformApplication();

        /**
         * @brief Get the Application singleton instance.
         * 
         * @return Application& 
         */
        static Application& GetApplication();

    private:
        /**
         * Singleton
         */
        static SharedRef<PlatformApplication> Application;

    };

}
