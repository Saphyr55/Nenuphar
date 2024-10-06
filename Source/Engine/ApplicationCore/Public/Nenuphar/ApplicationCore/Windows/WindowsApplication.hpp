#pragma once

#include "Nenuphar/ApplicationCore/ApplicationMessageHandler.hpp"
#include "Nenuphar/Core/Windows.hpp"

#if NP_PLATFORM_WINDOWS

#include "Nenuphar/ApplicationCore/PlatformApplication.hpp"
#include "Nenuphar/Common/Type/Type.hpp"

#include <vector>

namespace Nenuphar
{

    class WindowsWindow;

    using WindowsWindowRegistry = std::vector<SharedRef<WindowsWindow>>;

    SharedRef<WindowsWindow> FindWindowByHWND(WindowsWindowRegistry registry, HWND hwnd);
    

    /**
     * @brief 
     * 
     */
    class WindowsApplication : public PlatformApplication
    {
        friend WindowsWindow;

    public:
        static const TCHAR ApplicationClassName[];

        HINSTANCE GetHInstance() const;

    public:
        virtual bool PumpMessages() override;

        virtual void SetApplicationMessageHandler(SharedRef<ApplicationMessageHandler> handler) override;

        virtual SharedRef<Window> MakeWindow(const WindowDefinition& definition) override; 

        virtual bool Initialize() override;

        virtual Double GetAbsoluteTime() const override;

        virtual void Destroy() override;

        LRESULT ProcessMessage(HWND hwnd, UInt msg, WPARAM wParam, LPARAM lParam);

        inline UInt16 GetClassID() { return m_classID; }
        
    public:
        explicit WindowsApplication(HINSTANCE hinstance);
        ~WindowsApplication() override;

    private:
        SharedRef<ApplicationMessageHandler> m_applicationMessageHandler;
        WindowsWindowRegistry m_registry;

        UInt16 m_classID;
        HINSTANCE m_hinstance{};
    };


}// namespace Nenuphar

#endif