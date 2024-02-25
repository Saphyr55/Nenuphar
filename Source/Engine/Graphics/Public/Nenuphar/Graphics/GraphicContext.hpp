#pragma once

#include "Nenuphar/Common/Type/Type.hpp"

namespace Nenuphar
{

    class Window;

    class GraphicContext
    {
    public:

        static Void Init();

        static Ptr<GraphicContext> Create(Window& window);

        virtual void Current() const = 0;

        virtual void SwapBuffers() const = 0;

        virtual ~GraphicContext() = default;

    };

    using GraphicContextPtr = Ptr<GraphicContext>;

}