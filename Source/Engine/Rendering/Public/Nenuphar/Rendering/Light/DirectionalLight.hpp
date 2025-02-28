#pragma once

#include "Nenuphar/Math/Vector3.hpp"

namespace Nenuphar 
{
    
    struct DirectionalLight
    {
    public:
        Vector3f Direction = Vector3f(0.0f);
        Vector3f Ambient = Vector3f(0.1f);
        Vector3f Diffuse = Vector3f(0.1f);
        Vector3f Specular = Vector3f(0.0f);
    };

}