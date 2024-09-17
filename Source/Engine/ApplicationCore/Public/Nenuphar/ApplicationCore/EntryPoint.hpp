#pragma once

#include "Nenuphar/ApplicationCore/Application.hpp"
#include "Nenuphar/Common/Type/Type.hpp"
#include "Nenuphar/Core/Logger/Logger.hpp"



namespace Nenuphar
{
    /**
     * @brief Create a App Delegate object
     * 
     * @return SharedRef<AppDelegate> 
     */
    extern SharedRef<AppDelegate> AppDelegateCreate();

    /**
     * @brief 
     * 
     * @param argc 
     * @param argv 
     * @return int 
     */
    static int NMain(int argc, const char* argv[])
    {
        SharedRef<Logger> logger = MakeSharedRef<Logger>("Nenuphar.Engine");
        DefineLogger(logger);

        SharedRef<AppDelegate> appDelegate = AppDelegateCreate();

        if (!appDelegate)
        {
            NP_CRITICAL(NMain, "Unable to create the application delegate.");
            return EXIT_FAILURE;
        }

        SharedRef<Application> application = AppCreate(appDelegate);

        // TODO: Switching between application with asynchrone or parralism.
        AppMakeCurrent(application);

        application->Start();

        return EXIT_SUCCESS;
    }

}// namespace Nenuphar
