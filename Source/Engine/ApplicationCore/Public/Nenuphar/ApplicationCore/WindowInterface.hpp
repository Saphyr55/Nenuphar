#pragma once

#include "Nenuphar/Common/Common.hpp"

namespace Nenuphar
{

    class Application;
    class WindowDefinition;
    class WindowEventHandler;


    using WindowID = UInt16;


    enum class WindowMode : Int
    {
        Fullscreen,

        WindowedFullscreen,

        Windowed,
    };


    class WindowInterface
    {
    public:

        virtual const WindowEventHandler& GetWindowEventHandler() const = 0;

        virtual WindowID GetID() const = 0;

        virtual Void PoolEvent() const = 0;

        virtual Bool IsWindowMaximized() const = 0;

        virtual Bool IsWindowMinimized() const = 0;

        virtual Bool IsVisible() const = 0;

        virtual Void* GetOSWindowHandle() const = 0;

        virtual Void Hide() = 0;

        virtual Void Show() = 0;

        virtual Void Restore() = 0;

        virtual Void Maximaze() = 0;

        virtual Void Destroy() = 0;

        virtual Void ReshapeWindow(Int width, Int height) = 0;

        virtual Void SetTitle(StringView title) = 0;

        virtual ~WindowInterface() = default;

    };

}