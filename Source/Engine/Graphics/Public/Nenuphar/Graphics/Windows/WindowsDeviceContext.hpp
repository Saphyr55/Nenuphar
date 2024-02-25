#pragma once

#include "Nenuphar/ApplicationCore/Windows/WindowsWindow.hpp"

namespace Nenuphar
{
    
    class WindowsDeviceContext
    {
    public:
        WindowsDeviceContext(WindowsWindow& windowsWindow);
    
        HDC GetHDC();

        void Release();

    private:
        WindowsWindow& m_windowsWindow;
        HDC m_hdc;
        HWND m_hwnd;
    };

}