#pragma once

#include <forward_list>
#include <functional>

#include "Nenuphar/ApplicationCore/Application.hpp"
#include "Nenuphar/Common/Type/Type.hpp"
#include "Nenuphar/Core/Windows.hpp"
#include "Nenuphar/EventSystem.hpp"

namespace Nenuphar
{

    class WindowsWindow;


    using WindowsMessageHandler = std::function<Bool(HWND, UInt, WPARAM, LPARAM)>;


    struct WindowsMessagingDefinition
    {

        WindowsMessagingDefinition(const SharedRef<WindowsWindow>& InNativeWindow,
                                   HWND InHWnd,
                                   UInt InMessage,
                                   WPARAM InWParam,
                                   LPARAM InLParam);


        WeakPtr<WindowsWindow> NativeWindow;

        HWND HWnd;
        UInt Message;
        WPARAM WParam;
        LPARAM LParam;
    };


    class WindowsApplication final : public Application
    {
    public:
        
        SharedRef<Window> CreateApplicationWindow(WindowDefinition definition) override;

        bool IsRunning() override;

        WindowEventHandler& GetWindowEventHandler() override;

        EventBus& GetEventBus() override;

        void Stop() override;

        void SetRunning(bool is) override;

        void AddMessageHandler(WindowsMessageHandler& handler);

        void RemoveMessageHandler(WindowsMessageHandler& handler);

        Int ProcessMessage(HWND hwnd, UInt msg, WPARAM wParam, LPARAM lParam);
            
        HINSTANCE GetHInstance();

        friend LRESULT WndProcImpl(HWND hwnd, UInt msg, WPARAM wParam, LPARAM lParam);

        static LRESULT CALLBACK WndProc(HWND hwnd, UInt msg, WPARAM wParam, LPARAM lParam);

        explicit WindowsApplication(HINSTANCE hinstance = GetModuleHandle(nullptr));

    private:
        static SharedRef<WindowsApplication> WindowsApp;

        HINSTANCE hinstance;

        Bool isRunning;

        WindowEventHandler windowEventHandler;
        EventBus eventBus;

        std::forward_list<SharedRef<WindowsWindow>> windows;
        std::forward_list<SharedRef<WindowsMessageHandler>> handlers;
    };

} // namespace Dramatic
