#pragma once

#include "Nenuphar/ApplicationCore/WindowInterface.hpp"
#include "Nenuphar/Common/Type/Type.hpp"

namespace Nenuphar
{

    class Window;

    class GraphicContext
    {
    public:

        static Ptr<GraphicContext> Create(WindowInterface& window);

        virtual void Current() const = 0;

        virtual void SwapBuffers() const = 0;

        virtual ~GraphicContext() = default;

    };

    using GraphicContextPtr = Ptr<GraphicContext>;

}