#pragma once

#include "Nenuphar/ApplicationCore/Application.hpp"
#include "Nenuphar/ApplicationCore/ApplicationMessageHandler.hpp"

namespace Np = Nenuphar; 

class GenesisApplicationMessageHandler : public Np::ApplicationMessageHandler
{
public:
    virtual void OnWindowClose(SharedRef<Window> window) override
    {
        Np::AppStopCurrent();   
    }
    
};