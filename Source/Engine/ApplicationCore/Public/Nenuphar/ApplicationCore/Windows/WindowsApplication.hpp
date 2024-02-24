#pragma once

#include <functional>

#include "Nenuphar/ApplicationCore/PlatformApplication.hpp"
#include "Nenuphar/Common/Type/Type.hpp"
#include "Nenuphar/Core/Windows.hpp"
#include "Nenuphar/EventSystem.hpp"

namespace Nenuphar
{

    class WindowsWindow;

    using WindowsWindowRegistry = std::unordered_map<HWND, WindowsWindow*>;

    class WindowsApplication final : public PlatformApplication
    {
        friend WindowsWindow;

    public:
        static const TCHAR ApplicationClassName[];

        HINSTANCE GetHInstance() const;

        void Initialize() const;

        void Destroy() const override;

        static LRESULT CALLBACK ProcessMessage(HWND hwnd, UInt msg, WPARAM wParam, LPARAM lParam);

        explicit WindowsApplication(HINSTANCE hinstance = GetModuleHandle(nullptr));

        ~WindowsApplication() override;

    private:
        HINSTANCE hinstance{};
        static thread_local WindowsWindowRegistry WindowsWindowRegistry;
    };


}
