#pragma once

#include <forward_list>
#include <functional>
#include <set>

#include "Nenuphar/ApplicationCore/PlatformApplication.hpp"
#include "Nenuphar/ApplicationCore/Application.hpp"
#include "Nenuphar/Common/Type/Type.hpp"
#include "Nenuphar/Core/Windows.hpp"
#include "Nenuphar/EventSystem.hpp"

namespace Nenuphar
{

    class WindowsWindow;

    using WindowRegistry = std::unordered_map<WindowID, SharedRef<WindowInterface>>;

    class WindowsApplication final : public PlatformApplication
    {
        friend WindowsWindow;

    public:

        EventBus& GetEventBus() override;

        Int ProcessMessage(HWND hwnd, UInt msg, WPARAM wParam, LPARAM lParam);

        HINSTANCE GetHInstance() const;

        friend LRESULT WndProcImpl(HWND hwnd, UInt msg, WPARAM wParam, LPARAM lParam);

        static LRESULT CALLBACK WndProc(HWND hwnd, UInt msg, WPARAM wParam, LPARAM lParam);

        void Initialize() const;

        void Destroy() const override;

        WindowRegistry& GetRegistry() { return windowRegistry; }

    public:
        explicit WindowsApplication(HINSTANCE hinstance = GetModuleHandle(nullptr));

        ~WindowsApplication() override;

    private:
        void Emit(HWND handle, std::function<void(SharedRef<WindowInterface>)> func);

    private:
        static WindowsApplication* WindowsApp;
        HINSTANCE hinstance{};
        EventBus eventBus;
        WindowRegistry windowRegistry;
    };

}
