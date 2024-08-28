#include "Nenuphar/Rendering/RenderService.hpp"
#include "Nenuphar/Common/Instanciate.hpp"
#include "Nenuphar/Common/Type/Type.hpp"
#include "Nenuphar/Rendering/OpenGL/OpenGLRenderService.hpp"

namespace Nenuphar
{
    SharedRef<RenderService> RenderService::Instance()
    {
        static SharedRef<RenderService> service = MakeSharedRef<OpenGLRenderService>();
        return service;
    }
}