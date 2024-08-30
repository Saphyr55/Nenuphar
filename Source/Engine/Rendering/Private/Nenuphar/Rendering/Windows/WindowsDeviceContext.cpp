#include "Nenuphar/Rendering/Windows/WindowsDeviceContext.hpp"

#if NP_PLATFORM_WINDOWS

namespace Nenuphar
{

    WindowsDeviceContext::WindowsDeviceContext(WindowsWindow& windowsWindow)
        : m_windowsWindow(windowsWindow)
        , m_hdc(nullptr)
        , m_hwnd(nullptr)
    {
        m_hwnd = static_cast<HWND>(windowsWindow.GetOSWindowHandle());
        m_hdc = GetDC(m_hwnd);
    }

    HDC WindowsDeviceContext::GetHDC()
    {
        return m_hdc;
    }

    void WindowsDeviceContext::Release()
    {
        ReleaseDC(m_hwnd, m_hdc);
    }



}

#endif