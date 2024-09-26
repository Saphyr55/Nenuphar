#pragma once

#include "Nenuphar/Common/Type/Type.hpp"
#include "RenderHandle.hpp"


namespace Nenuphar 
{
    
    class Texture : public RenderHandle
    {
    public:
        virtual void Destroy() override { }

    private:
        UInt m_id;
    };

}