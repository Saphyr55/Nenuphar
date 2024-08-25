#pragma once

#include "Nenuphar/Common/Type/Type.hpp"
#include "Nenuphar/Rendering/OpenGL/OpenGLShader.hpp"
#include "Nenuphar/Rendering/Texture.hpp"
#include "Nenuphar/Rendering/Vertex.hpp"

#include <vector>

namespace Nenuphar
{
    
    using MeshId = std::size_t;
    
    struct Mesh
    {   
        std::vector<Vertex> Vertices;
        std::vector<VIndice> Indices;
        std::vector<Texture> Textures;
    };


} // namespace Nenuphar