#pragma once

#include "Nenuphar/ApplicationCore/Application.hpp"
#include "Nenuphar/ApplicationCore/PlatformApplication.hpp"

#include "Nenuphar/Common/Type/Type.hpp"

namespace Nenuphar 
{
    
    class ApplicationImpl : public Application
    {
    public:        
        virtual void Initialize() override;
        
        virtual void Tick(Double deltaTime) override;
    
        virtual void Start() override;

        virtual void Close() override;
    
    public:
        virtual Bool IsRunning() const override;

        virtual Bool IsSuspended() const override;

        virtual Double GetLastTime() const override;
        
        virtual SharedRef<PlatformApplication> GetPlatformApplication() override;

        ApplicationImpl(SharedRef<AppDelegate> appDelegate);
        ~ApplicationImpl() = default;

    private:   
        Bool m_isRunning;
        Bool m_isSuspended;
        Double m_lastTime;
    
        SharedRef<AppDelegate> m_appDelegate;
        SharedRef<PlatformApplication> m_platformApplication;
    };

}