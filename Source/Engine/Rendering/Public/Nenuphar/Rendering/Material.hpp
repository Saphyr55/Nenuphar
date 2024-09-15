#pragma once

#include "Nenuphar/Common/Type/Type.hpp"
#include "Nenuphar/Math/Vector3.hpp"
#include "Nenuphar/Rendering/Texture.hpp"

namespace Nenuphar
{
    
    struct Material
    {
        UInt Id;

        Vector3f Diffuse;
        Vector3f Specular;
        Float Shininess;

        Texture DiffuseTexture;
        Texture SpecularTexture;
    };

}