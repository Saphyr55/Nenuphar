#pragma once

#include <vector>

#include "Nenuphar/Rendering/Mesh.hpp"
#include "Nenuphar/Rendering/OpenGL/OpenGLVertexArray.hpp"
#include "Nenuphar/Rendering/Vertex.hpp"

namespace Nenuphar
{

    struct OpenGLMesh
    {   
        Mesh mesh;
        OpenGLVertexArray VAO;
        Int Count;
    };

    using OpenGLMeshStorage = std::vector<OpenGLMesh>;
    static OpenGLMeshStorage Storage;

    MeshId OpenGLPersistMesh(const Mesh& mesh);

    void OpenGLDrawMesh(const MeshId& id);

}
