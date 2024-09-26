#pragma once

#include "Nenuphar/ApplicationCore/Application.hpp"
#include "Nenuphar/ApplicationCore/Clock.hpp"
#include "Nenuphar/ApplicationCore/PlatformApplication.hpp"

#include "Nenuphar/Common/Type/Type.hpp"

namespace Nenuphar 
{
    
    class ApplicationImpl : public Application
    {
    public:
        virtual bool Initialize() override;
        
        virtual void Tick(Double deltaTime) override;
    
        virtual void Start() override;

        virtual void Close() override;
    
    public:
        virtual void Stop() override;

        virtual void Resume() override;

        virtual void Suspend() override;
        
        virtual bool IsRunning() const override;

        virtual bool IsSuspended() const override;

        virtual double GetLastTime() const override;
        
        ApplicationImpl(SharedRef<AppDelegate> appDelegate);
        ~ApplicationImpl() = default;

    private:   
        bool m_isRunning;
        bool m_isSuspended;
        double m_lastTime;

        Clock m_clock;
        
        SharedRef<AppDelegate> m_appDelegate;
    };

}