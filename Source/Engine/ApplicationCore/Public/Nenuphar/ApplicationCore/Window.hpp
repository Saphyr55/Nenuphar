#pragma once

#include "Nenuphar/Common/Common.hpp"

namespace Nenuphar
{

    class Application;
    class WindowEventHandler;
    class WindowSignals;

    using WindowID = UInt16;


    struct WindowDefinition
    {
        String Title;
        Float Width;
        Float Height;
    };


    enum class WindowMode : Int
    {
        Fullscreen,

        WindowedFullscreen,

        Windowed,
    };


    class Window
    {
    public:

        virtual const WindowDefinition& GetWindowDefinition() const = 0;

        virtual const WindowSignals& GetWindowSignals() const = 0;

        virtual WindowID GetID() const = 0;

        virtual Void PoolEvent() const = 0;

        virtual Bool IsWindowMaximized() const = 0;

        virtual Bool IsWindowMinimized() const = 0;

        virtual Bool IsVisible() const = 0;

        virtual Void* GetOSWindowHandle() const = 0;

        virtual Void Hide() = 0;

        virtual Void Show() = 0;

        virtual Void Restore() = 0;

        virtual Void Maximize() = 0;

        virtual Void Destroy() = 0;

        virtual Void ReshapeWindow(Int width, Int height) = 0;

        virtual Void SetTitle(StringView title) = 0;

        virtual ~Window() = default;

    };

}