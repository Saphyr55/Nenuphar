#include "Nenuphar/Rendering/OpenGL/OpenGLRenderer.hpp"
#include "Nenuphar/Asset/AssetRegistry.hpp"
#include "Nenuphar/Rendering/Mesh.hpp"
#include "Nenuphar/Rendering/OpenGL/OpenGLMesh.hpp"
#include "Nenuphar/Rendering/OpenGL/OpenGLTexture.hpp"
#include "Nenuphar/Rendering/Texture.hpp"
#include "Nenuphar/Rendering/TextureAsset.hpp"

namespace Nenuphar
{

    // TODO: Use a sparse set and the pagination technique to have better perfomance.
    static std::vector<std::vector<MeshId>> ModelStorage;


    Texture OpenGLRenderer::PersistTexture(SharedRef<TextureAsset> asset,
                                           const PersitTextureOption& option) const
    {
        SharedRef<OpenGLTexture2D> texture = CreateOpenGLTexture2D(0);
        texture->Bind();
        DefaultParameterTexture(asset->Information, OpenGLTexture2D::Parameter());
        texture->Unbind();

        if (option.ReleaseData)
        {
            option.Registry.GetLoader<TextureAsset>()->Unload(asset);
        }
        
        return texture->GetHandle();
    }

    
    ModelId OpenGLRenderer::PersistModel(const Model& model) const
    {
        ModelId id = ModelStorage.size();
        ModelStorage.push_back({ });
        for (auto& mesh: model.Meshes)
        {
            ModelStorage[id].push_back(PersistMesh(mesh));
        }
        return id;
    }


    MeshId OpenGLRenderer::PersistMesh(const Mesh& mesh) const
    {
        static MeshId LastId = 0;
        MeshId id = LastId++;
        MeshStorage::GetGlobalStorage().insert({id, mesh});
        OpenGLPersistMesh(id);
        return id;
    }


    void OpenGLRenderer::TextureModel(const MeshId& model, const Texture& texture) const
    {
        for (const MeshId& mesh: ModelStorage[model])
        {
            TextureMesh(mesh, texture);
        }
    }

    
    void OpenGLRenderer::TextureMesh(const MeshId& meshId, const Texture& texture) const
    {
        Mesh& mesh = MeshStorage::GetGlobalStorage().at(meshId);
        mesh.Textures.push_back(texture);
    }

    
    void OpenGLRenderer::DrawMesh(const Shader& shader, const MeshId& mesh) const
    {
        shader.Use();
        OpenGLDrawMesh(mesh);
    }

    
    void OpenGLRenderer::DrawModel(const Shader& shader, const ModelId& model) const
    {
        shader.Use();
        for (const MeshId& mesh: ModelStorage[model])
        {
            OpenGLDrawMesh(mesh);
        }
    }

}
