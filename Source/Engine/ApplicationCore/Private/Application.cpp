#include "Nenuphar/ApplicationCore/Application.hpp"

namespace Np = Nenuphar;

#ifdef NP_PLATFORM_WINDOWS

#include <Nenuphar/ApplicationCore/Windows/WindowsApplication.hpp>

Np::Ptr<Np::Application> Np::Application::CreateApplication()
{
    return std::make_unique<Np::WindowsApplication>();
}

#else

Np::Ptr<Np::Application> Np::Application::CreateApplication()
{
    return nullptr;
}

#endif
