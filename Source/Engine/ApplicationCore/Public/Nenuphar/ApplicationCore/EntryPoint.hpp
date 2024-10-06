#pragma once

#include "Nenuphar/ApplicationCore/Application.hpp"
#include "Nenuphar/ApplicationCore/PlatformApplication.hpp"
#include "Nenuphar/Common/Type/Type.hpp"
#include "Nenuphar/Core/Logger/Logger.hpp"

#include <cstdlib>


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
        
        bool isSuccess = PlatformAppGet()->Initialize();
        if (!isSuccess)
        {
            NP_CRITICAL(PlatformApplication::Initialize, "Impossible to load the platform application.");
            return isSuccess;
        }
    
        SharedRef<AppDelegate> appDelegate = AppDelegateCreate();

        if (!appDelegate)
        {
            NP_CRITICAL(NMain, "Unable to create the application delegate.");
            return EXIT_FAILURE;
        }

        SharedRef<Application> application = AppCreate(appDelegate);

        // TODO: Switching between application with asynchrone or parralism.
        AppMakeCurrent(application);

        if (!application->Initialize())
        {
            return EXIT_FAILURE;
        }

        application->Start();
        application->Stop();

        return EXIT_SUCCESS;
    }

}// namespace Nenuphar
