#pragma once

#include "Nenuphar/Common/Type/Type.hpp"
#include "Nenuphar/Math/Matrix4.hpp"

namespace Nenuphar 
{
    
    struct MainUniformBlock
    {
        Matrix4f UProjection;
        Matrix4f UView;
        Matrix4f UModel;
    };

    class UniformBuffer
    {
    public:
        

    public:
        virtual ~UniformBuffer() = 0;
    
    };

}