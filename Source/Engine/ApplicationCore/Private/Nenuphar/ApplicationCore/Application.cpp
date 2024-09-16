#include "Nenuphar/ApplicationCore/Application.hpp"
#include "ApplicationImpl.hpp"
#include "Nenuphar/Common/Type/Type.hpp"
#include "Nenuphar/Core/Core.hpp"

namespace Nenuphar 
{
    
    static SharedRef<Application> GApplication;

    SharedRef<Application> AppCreate(SharedRef<AppDelegate> appDelegate)
    {
        NCHECK(appDelegate)
        SharedRef<Application> application = MakeSharedRef<ApplicationImpl>(appDelegate);
        return application;
    }

    void AppMakeCurrent(SharedRef<Application> application)
    {
        GApplication = application;
    }

    SharedRef<Application> AppGetCurrent()
    {
        return GApplication;
    }

}