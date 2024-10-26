#pragma once

#include "Nenuphar/Common/Type/Type.hpp"
#include "Nenuphar/Rendering/Framebuffer.hpp"

namespace Nenuphar 
{
    class OpenGLFramebuffer : public Framebuffer
    {  
    public:
        void Initialize();

        virtual void Destroy() override;

    private:
        UInt m_handle; 
    };

}