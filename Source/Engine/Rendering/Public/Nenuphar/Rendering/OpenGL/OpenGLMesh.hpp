#pragma once

#include <vector>

#include "Nenuphar/Common/Type/Type.hpp"
#include "Nenuphar/Rendering/Mesh.hpp"
#include "Nenuphar/Rendering/OpenGL/OpenGLVertexArray.hpp"
#include "Nenuphar/Rendering/Shader.hpp"
#include "Nenuphar/Rendering/Vertex.hpp"

namespace Nenuphar
{

    struct OpenGLMesh
    {   
        SharedRef<Mesh> mesh;
        SharedRef<OpenGLVertexArray> VAO;
        Int Count;
    };

    using OpenGLMeshStorage = std::vector<OpenGLMesh>;
    static OpenGLMeshStorage Storage;

    MeshId OpenGLPersistMesh(SharedRef<Mesh> mesh);

    void OpenGLDrawMesh(const MeshId& id);

}
