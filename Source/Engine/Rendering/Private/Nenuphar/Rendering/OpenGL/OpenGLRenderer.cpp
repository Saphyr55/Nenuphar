#include "Nenuphar/Rendering/OpenGL/OpenGLRenderer.hpp"
#include "Nenuphar/Rendering/OpenGL/OpenGLMesh.hpp"

namespace Nenuphar
{
    
    // TODO: Better way to store models.
    static std::vector<std::vector<MeshId>> ModelsStorage;

    ModelId OpenGLRenderer::PersistModel(const Model& model) const
    {
        ModelId id = ModelsStorage.size();
        for (auto& mesh: model.Meshes)
        {
            ModelsStorage[id].push_back(PersistMesh(mesh));
        }
        return id;
    }

    MeshId OpenGLRenderer::PersistMesh(const Mesh& mesh) const
    {
        return OpenGLPersistMesh(mesh);
    }

    void OpenGLRenderer::DrawMesh(const Shader& shader, const MeshId& mesh) const
    {
        shader.Use();
        OpenGLDrawMesh(mesh);
    }

}
