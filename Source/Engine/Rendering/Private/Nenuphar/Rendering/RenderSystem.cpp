#include "Nenuphar/Rendering/RenderSystem.hpp"

#include "Nenuphar/Core/Core.hpp"
#include "Nenuphar/Rendering/OpenGL/OpenGLRenderSystem.hpp"

namespace Nenuphar
{

    RenderSystem& RenderSystem::Instance(GraphicsAPI type)
    {
        static auto renderSystem = MakeUnique<OpenGLRenderSystem>();

        return *renderSystem;
    }

}