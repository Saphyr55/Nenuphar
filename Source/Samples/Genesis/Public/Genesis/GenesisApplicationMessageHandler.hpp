#pragma once

#include "Nenuphar/ApplicationCore/Application.hpp"
#include "Nenuphar/ApplicationCore/ApplicationMessageHandler.hpp"

namespace Np = Nenuphar; 

class GenesisApplicationMessageHandler : public Np::ApplicationMessageHandler
{
public:
    virtual void OnWindowClose(Np::SharedRef<Np::Window> window) override
    {
        window->Destroy();
        Np::AppStopCurrent();
    }

};