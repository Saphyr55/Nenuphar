#pragma once

#include "Nenuphar/Core/Windows.hpp"

#if NP_PLATFORM_WINDOWS

#include "Nenuphar/ApplicationCore/PlatformApplication.hpp"
#include "Nenuphar/Common/Type/Type.hpp"

namespace Nenuphar
{

    class WindowsWindow;
    
    /**
     * @brief 
     * 
     * @param handle 
     * @param windowsWindow 
     */
    void RegisterWindowsWindow(HWND handle, WindowsWindow* windowsWindow);

    /**
     * @brief 
     * 
     */
    class WindowsApplication final : public PlatformApplication
    {
        friend WindowsWindow;

    public:
        static const TCHAR ApplicationClassName[];

        HINSTANCE GetHInstance() const;

    public:
        virtual void Initialize() override;

        virtual Double GetAbsoluteTime() const override;

        virtual void Destroy() override;

    private:
        static LRESULT CALLBACK ProcessMessage(HWND hwnd, UInt msg, WPARAM wParam, LPARAM lParam);
        
    public:
        explicit WindowsApplication(HINSTANCE hinstance);
        ~WindowsApplication() override;

    private:
        UInt16 m_classID;
        HINSTANCE m_hinstance{};
    };


}// namespace Nenuphar

#endif