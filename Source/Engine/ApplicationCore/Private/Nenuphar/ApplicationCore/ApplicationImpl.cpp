#include "Nenuphar/ApplicationCore/ApplicationImpl.hpp"
#include "Nenuphar/ApplicationCore/PlatformApplication.hpp"
#include "Nenuphar/Common/Type/Type.hpp"
#include "Nenuphar/Core/Logger/Logger.hpp"

namespace Nenuphar
{

    bool ApplicationImpl::Initialize()
    {
        bool isSuccess = m_appDelegate->OnInitialize();
        if (!isSuccess)
        {
            NP_CRITICAL(Application::Initialize, "Impossible to load the delegate application.");
            return isSuccess;
        }

        // Start the clock
        ClockStart(PlatformAppGet(), m_clock);
        ClockTick(PlatformAppGet(), m_clock);
        m_lastTime = m_clock.Elapsed;

        return isSuccess;
    }

    void ApplicationImpl::Tick(Double deltaTime)
    {
        m_appDelegate->OnTick(deltaTime);
    }

    void ApplicationImpl::Start()
    {
        m_isRunning = true;
        
        Double runningTime = 0;
        Double count = 0;

        // TODO: Supply the "frame rate" by the application context.   
        Double targetSeconds = 1.0 / 60;
        
        while (IsRunning())
        {
            if (!IsSuspended())
            {
                ClockTick(PlatformAppGet(), m_clock);
                Double currentTime = m_clock.Elapsed;
                Double deltaTime = currentTime - m_lastTime;
                Double startTime = PlatformAppGet()->GetAbsoluteTime();

                Tick(deltaTime);

                Double endTime = PlatformAppGet()->GetAbsoluteTime();
                Double elapsedTime = endTime - startTime;
                runningTime += elapsedTime;
                Double remainingSeconds = targetSeconds - elapsedTime;

                // TODO: Need a sleep to continue this.
                // ClockLimitCount(m_platformApplication, )
                m_lastTime = currentTime;
            } 
            else
            {
                m_appDelegate->OnSuspend();
            }

            if (!PlatformAppGet()->PumpMessages())
            {
                m_isRunning = false;
            }
        }

    }

    void ApplicationImpl::Close()
    {
        ClockStop(m_clock);
        m_appDelegate->OnClose();
        PlatformAppGet()->Destroy();
    }

    void ApplicationImpl::Stop()
    {
        m_isRunning = false;
    }

    void ApplicationImpl::Resume()
    {
        m_isSuspended = false;
    }

    void ApplicationImpl::Suspend()
    {
        m_isSuspended = true;
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

    ApplicationImpl::ApplicationImpl(SharedRef<AppDelegate> appDelegate)
        : m_isRunning(false)
        , m_isSuspended(false)
        , m_lastTime(0.0)
        , m_appDelegate(appDelegate)
    {
    }

} // namespace Nenuphar