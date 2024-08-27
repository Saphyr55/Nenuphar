#pragma once

#include <unordered_map>
#include <vector>

#include "Nenuphar/Common/Type/Type.hpp"
#include "Nenuphar/Rendering/Mesh.hpp"
#include "Nenuphar/Rendering/OpenGL/OpenGLVertexArray.hpp"


namespace Nenuphar
{

    struct OpenGLMesh
    {   
        MeshId Id;
        UniquePtr<OpenGLVertexArray> VAO;
        Int Count;
    };

    // TODO: Use a sparse set and the pagination technique to have better perfomance.
    class OpenGLMeshStorage
    {
    public:
        using TStorage = std::unordered_map<MeshId, OpenGLMesh>;

        static TStorage& GetGlobalStorage();

    private:
        TStorage m_storage;
        static OpenGLMeshStorage s_mainStorage;
    };

    void OpenGLPersistMesh(const MeshId& mesh);

    void OpenGLDrawMesh(const MeshId& id);

}
