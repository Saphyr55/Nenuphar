#include "Nenuphar/ApplicationCore/ApplicationImpl.hpp"
#include "Nenuphar/ApplicationCore/PlatformApplication.hpp"

namespace Nenuphar
{

    void ApplicationImpl::Initialize()
    {
        m_platformApplication->Initialize();
        m_appDelegate->OnInitialize();
    }


    void ApplicationImpl::Tick(Double deltaTime)
    {
        m_appDelegate->OnTick(deltaTime);
    }


    void ApplicationImpl::Start()
    {
        m_isRunning = true;

        Initialize();

        while (IsRunning())
        {
            Tick(0.0);
        }

        Close();

        m_isRunning = false;
    }


    void ApplicationImpl::Close()
    {
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
        , m_platformApplication(PlatformAppCreate())
    {
    }

} // namespace Nenuphar