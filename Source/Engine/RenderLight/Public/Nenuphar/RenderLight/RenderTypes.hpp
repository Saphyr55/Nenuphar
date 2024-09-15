#pragma once

#include "Nenuphar/Math/Vector3.hpp"

namespace Nenuphar 
{

    struct DirectionalLight
    {
		Vector3f Position;

        Vector3f Ambient = Vector3f(1.0f);
        Vector3f Diffuse = Vector3f(1.0f);
        Vector3f Specular = Vector3f(1.0f);
    };

}