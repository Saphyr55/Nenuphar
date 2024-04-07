#pragma once

#include "WindowDefinition.hpp"
#include "WindowInterface.hpp"
#include "PlatformApplication.hpp"

namespace Nenuphar
{

    class WindowBase;

    class Window : public WindowInterface
    {
    public:

        Void PoolEvent() const override;

        const WindowSignals& GetWindowSignals() const override;

        const WindowEventHandler& GetWindowEventHandler() const override;

        WindowID GetID() const override;

        Bool IsWindowMaximized() const override;

        Bool IsWindowMinimized() const override;

        Bool IsVisible() const override;

        Void* GetOSWindowHandle() const override;

        Void Hide() override;

        Void Show() override;

        Void Restore() override;

        Void Maximize() override;

        Void Destroy() override;

        Void ReshapeWindow(Int width, Int height) override;

        Void SetTitle(StringView title) override;

        inline WindowBase& Base() { return *m_base; }

    public:
        Window(
            const WindowDefinition& definition, 
            PlatformApplication& app = PlatformApplication::GetPlatformApplication());

        Window(StringView title, Int width, Int height);

        ~Window() override = default;

    private:
        SharedRef<WindowBase> m_base;
    };
}
