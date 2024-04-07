#pragma once

#include "Nenuphar/ApplicationCore/WindowDefinition.hpp"
#include "Nenuphar/ApplicationCore/WindowInterface.hpp"

namespace Nenuphar
{

    class EventBus;
    class PlatformApplication;

    class WindowBase : public WindowInterface
    {
    public:
        static SharedRef<WindowBase> Create(
            WindowDefinition definition, 
            PlatformApplication& app);

        virtual const WindowEventHandler& GetWindowEventHandler() const override = 0;

        virtual WindowID GetID() const override = 0;

        virtual Void PoolEvent() const override = 0;

        virtual Bool IsWindowMaximized() const override = 0;

        virtual Bool IsWindowMinimized() const override = 0;

        virtual Bool IsVisible() const override = 0;

        virtual Void* GetOSWindowHandle() const override = 0;

        virtual Void Hide() override = 0;

        virtual Void Show() override = 0;

        virtual Void Restore() override = 0;

        virtual Void Maximize() override = 0;

        virtual Void Destroy() override = 0;

        virtual Void ReshapeWindow(Int width, Int height) override = 0;

        virtual Void SetTitle(StringView title) override = 0;

        ~WindowBase() override = default;
    };

}

