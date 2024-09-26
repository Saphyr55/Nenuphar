#pragma once

#include "Nenuphar/Common/Type/Type.hpp"
#include "Nenuphar/Core/Core.hpp"

#if NP_PLATFORM_WINDOWS

#include "Nenuphar/ApplicationCore/Windows/WindowsWindow.hpp"

namespace Nenuphar
{
    
    class WindowsDeviceContext
    {
    public:
        WindowsDeviceContext(SharedRef<WindowsWindow> windowsWindow);
    
        HDC GetHDC();

        void Release();

    private:
        SharedRef<WindowsWindow> m_windowsWindow;
        HDC m_hdc;
        HWND m_hwnd;
    };

}

#endif