#pragma once

#include <unordered_map>

#include "Nenuphar/Common/Type/Type.hpp"
#include "Nenuphar/Rendering/Mesh.hpp"
#include "Nenuphar/Rendering/OpenGL/OpenGLVertexArray.hpp"


namespace Nenuphar
{
    class UniformRegistry;

    struct OpenGLMesh
    {
        MeshId Id;
        SharedRef<OpenGLVertexArray> VAO;
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

    void OpenGLSubmitMesh(const MeshId& mesh);

    void OpenGLDrawMesh(SharedRef<UniformRegistry> registry, const MeshId& id);

}// namespace Nenuphar
