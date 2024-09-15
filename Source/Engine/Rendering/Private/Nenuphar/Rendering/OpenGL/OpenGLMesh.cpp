#include "Nenuphar/Rendering/OpenGL/OpenGLMesh.hpp"
#include "Nenuphar/Common/Instanciate.hpp"
#include "Nenuphar/Common/Type/Type.hpp"
#include "Nenuphar/Core/Debug.hpp"
#include "Nenuphar/Math/Vector3.hpp"
#include "Nenuphar/Rendering/Mesh.hpp"
#include "Nenuphar/Rendering/OpenGL/OpenGLBuffer.hpp"
#include "Nenuphar/Rendering/OpenGL/OpenGLDebugger.hpp"
#include "Nenuphar/Rendering/OpenGL/OpenGLLayoutBuffer.hpp"
#include "Nenuphar/Rendering/OpenGL/OpenGLShader.hpp"
#include "Nenuphar/Rendering/OpenGL/OpenGLTexture.hpp"
#include "Nenuphar/Rendering/OpenGL/OpenGLVertexArray.hpp"
#include "Nenuphar/Rendering/OpenGL/Uniform.hpp"
#include "Nenuphar/Rendering/Texture.hpp"
#include "Nenuphar/Rendering/Vertex.hpp"


#include <cstdlib>


namespace Nenuphar
{

    enum class TextureTypeModel
    {
        Specular,
        Diffuse
    };

    struct TextureExtraInfo
    {
        Texture Texture;
        TextureTypeModel TTM;
    };

    OpenGLMeshStorage OpenGLMeshStorage::s_mainStorage;

    OpenGLMeshStorage::TStorage& OpenGLMeshStorage::GetGlobalStorage()
    {
        return OpenGLMeshStorage::s_mainStorage.m_storage;
    }

    void OpenGLPersistMesh(const MeshId& meshId)
    {
        Mesh& mesh = MeshStorage::GetGlobalStorage()[meshId];
        Int count = mesh.Indices.size();

        auto vao = MakeUnique<OpenGLVertexArray>();
        OpenGLArrayBuffer<> vbo(mesh.Vertices);
        OpenGLElementBuffer ebo(mesh.Indices);

        LinkBuffer(vbo, LayoutVertex);

        vao->Unbind();
        vbo.Unbind();
        ebo.Unbind();

        OpenGLMeshStorage::GetGlobalStorage().insert({meshId,
                                                      OpenGLMesh(meshId, std::move(vao), count)});
    }

    void OpenGLDrawMesh(UniformRegistry& registry, const MeshId& id)
    {
        NCHECK(OpenGLMeshStorage::GetGlobalStorage().contains(id))
        NCHECK(MeshStorage::GetGlobalStorage().contains(id))

        auto storage = OpenGLTextureStorage::GetGlobalStorageTexture2D();
        auto& glMesh = OpenGLMeshStorage::GetGlobalStorage().at(id);
        auto& mesh = MeshStorage::GetGlobalStorage().at(id);

        std::vector<TextureExtraInfo> textures;

        for (auto& material: mesh.Materials)
        {
            TextureExtraInfo diffuseTexture;
            diffuseTexture.Texture = material.DiffuseTexture;
            diffuseTexture.TTM = TextureTypeModel::Diffuse;

            TextureExtraInfo specularTexture;
            specularTexture.Texture = material.DiffuseTexture;
            specularTexture.TTM = TextureTypeModel::Diffuse;

            textures.push_back(diffuseTexture);
            textures.push_back(specularTexture);

            registry.Get<Vector3f>("UMaterial.Diffuse").UpdateValue(material.Diffuse);
            registry.Get<Vector3f>("UMaterial.Specular").UpdateValue(material.Specular);
            registry.Get<Float>("UMaterial.Shininess").UpdateValue(material.Shininess);
        }

        for (auto i = 0; i < textures.size(); i++)
        {
            TextureExtraInfo& textureExtraInfo = textures.at(i);

            if (storage.contains(textureExtraInfo.Texture))
            {
                SharedRef<OpenGLTexture2D> openGLTexture = storage.at(textureExtraInfo.Texture);

                ActiveTexture(i);

                switch (textureExtraInfo.TTM)
                {
                    case TextureTypeModel::Diffuse: {
                        registry.Get<Int>("UTexture").UpdateValue((Int)i);
                        registry.Get<Int>("UMaterial.DiffuseTexture").UpdateValue((Int)i);
                    }
                    break;
                    case TextureTypeModel::Specular: {
                        registry.Get<Int>("UMaterial.SpecularTexture").UpdateValue((Int)i);
                    }
                    break;
                }

                openGLTexture->Bind();
            }

        }

        glMesh.VAO->Bind();
        NP_GL_CHECK_CALL(glDrawElements(GL_TRIANGLES, glMesh.Count, GL_UNSIGNED_INT, 0));
        glMesh.VAO->Unbind();

        ActiveTexture(0);
    }
}// namespace Nenuphar