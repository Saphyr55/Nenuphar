#include "Nenuphar/ApplicationCore/ApplicationImpl.hpp"
#include "Nenuphar/ApplicationCore/PlatformApplication.hpp"
#include "Nenuphar/Common/Type/Type.hpp"

namespace Nenuphar
{

    void ApplicationImpl::Initialize()
    {
        m_platformApplication->Initialize();
        m_appDelegate->OnInitialize();

        // Start the clock
        ClockStart(m_platformApplication, m_clock);
        ClockTick(m_platformApplication, m_clock);
        m_lastTime = m_clock.Elapsed;
    }

    void ApplicationImpl::Tick(Double deltaTime)
    {
        m_appDelegate->OnTick(deltaTime);
    }

    void ApplicationImpl::Start()
    {
        m_isRunning = true;

        Initialize();
        
        Double runningTime = 0;
        Double count = 0;
        
        // TODO: Supply the "frame rate" by the application context.   
        Double targetSeconds = 1.0 / 60;
        
        while (IsRunning())
        {
            if (!IsSuspended())
            {
                ClockTick(m_platformApplication, m_clock);
                Double currentTime = m_clock.Elapsed;
                Double deltaTime = currentTime - m_lastTime;
                Double startTime = m_platformApplication->GetAbsoluteTime();

                Tick(deltaTime);

                Double endTime = m_platformApplication->GetAbsoluteTime();
                Double elapsedTime = endTime - startTime;
                runningTime += elapsedTime;
                Double remainingSeconds = targetSeconds - elapsedTime;

                // TODO: Need a sleep to continue this.
                // ClockLimitCount(m_platformApplication, )

                m_lastTime = currentTime;
            }
        }

        Close();

        m_isRunning = false;
    }


    void ApplicationImpl::Close()
    {
        ClockStop(m_clock);
        m_appDelegate->OnClose();
        m_platformApplication->Destroy();
    }


    Bool ApplicationImpl::IsRunning() const
    {
        return m_isRunning;
    }


    Bool ApplicationImpl::IsSuspended() const
    {
        return m_isSuspended;
    }

    Double ApplicationImpl::GetLastTime() const
    {
        return m_lastTime;
    }

    SharedRef<PlatformApplication> ApplicationImpl::GetPlatformApplication()
    {
        return m_platformApplication;
    }

    ApplicationImpl::ApplicationImpl(SharedRef<AppDelegate> appDelegate)
        : m_isRunning(false)
        , m_isSuspended(false)
        , m_lastTime(0.0)
        , m_appDelegate(appDelegate)
        , m_platformApplication(PlatformAppGet())
    {
    }

} // namespace Nenuphar