#include "Nenuphar/Rendering/Windows/WindowsDeviceContext.hpp"
#include "Nenuphar/Common/Type/Type.hpp"
#include "Nenuphar/Core/Debug.hpp"

#if NP_PLATFORM_WINDOWS

namespace Nenuphar
{

    WindowsDeviceContext::WindowsDeviceContext(SharedRef<WindowsWindow> windowsWindow)
        : m_windowsWindow(windowsWindow)
        , m_hdc(nullptr)
        , m_hwnd(nullptr)
    {
        NCHECK(windowsWindow)
        m_hwnd = static_cast<::HWND>(windowsWindow->GetOSWindowHandle());
        m_hdc = ::GetDC(m_hwnd);
    }

    ::HDC WindowsDeviceContext::GetHDC()
    {
        return m_hdc;
    }

    void WindowsDeviceContext::Release()
    {
        ::ReleaseDC(m_hwnd, m_hdc);
    }



}

#endif