#include "Nenuphar/Graphics/Mesh.hpp"
#include "Nenuphar/Common/Type/Type.hpp"
#include "Nenuphar/Core/Debug.hpp"
#include "Nenuphar/Rendering/CommandBuffer.hpp"
#include "Nenuphar/Rendering/RenderDevice.hpp"
#include "Nenuphar/Rendering/Texture.hpp"
#include "Nenuphar/Rendering/UniformRegistry.hpp"

namespace Nenuphar
{

    enum class TextureTypeModel
    {
        Specular,
        Diffuse
    };

    struct TextureExtraInfo
    {
        SharedRef<Texture> Texture;
        TextureTypeModel TTM;
    };
    
    void Mesh::Destroy()
    {
        RenderHandle->Destroy();
    }

    void RenderCommandSubmitMesh(SharedRef<RenderDevice> renderDevice, Mesh& mesh)
    {
        mesh.RenderHandle = renderDevice->CreateRenderHandle(mesh.Vertices, mesh.Indices);
    }

    void ApplyMaterial(const Material& material, SharedRef<UniformRegistry> registry)
    {
        registry->Get<Vector3f>("UMaterial.Diffuse").UpdateValue(material.Diffuse);
        registry->Get<Vector3f>("UMaterial.Specular").UpdateValue(material.Specular);
        registry->Get<Float>("UMaterial.Shininess").UpdateValue(material.Shininess);
    }

    void ApplyMaterialTexture(const TextureExtraInfo& textureExtraInfo, SharedRef<UniformRegistry> registry, UInt slot)
    {
        switch (textureExtraInfo.TTM)
        {
            case TextureTypeModel::Diffuse: {
                registry->Get<Int>("UTexture").UpdateValue((Int)slot);
                registry->Get<Int>("UMaterial.DiffuseTexture").UpdateValue((Int)slot);
                break;
            }
            case TextureTypeModel::Specular: {
                registry->Get<Int>("UMaterial.SpecularTexture").UpdateValue((Int)slot);
                break;
            }
        }
    }

    void RenderCommandDrawMesh(SharedRef<CommandBuffer> commandBuffer,
                               SharedRef<UniformRegistry> registry,
                               const Mesh& mesh)
    {
        std::vector<TextureExtraInfo> textures;

        for (auto& material: mesh.Materials)
        {
            if (material.DiffuseTexture)
            {
                TextureExtraInfo diffuseTexture;
                diffuseTexture.Texture = material.DiffuseTexture;
                diffuseTexture.TTM = TextureTypeModel::Diffuse;

                textures.push_back(std::move(diffuseTexture));
            }

            if (material.SpecularTexture)
            {
                TextureExtraInfo specularTexture;
                specularTexture.Texture = material.SpecularTexture;
                specularTexture.TTM = TextureTypeModel::Specular;

                textures.push_back(std::move(specularTexture));
            }

            // TODO: Pipepline and binding.
            commandBuffer->Record([registry, material]() {
                ApplyMaterial(material, registry);
            });
        }

        for (std::size_t slot = 0; slot < textures.size(); slot++)
        {
            TextureExtraInfo& textureExtraInfo = textures.at(slot);

            commandBuffer->BindTexture(textureExtraInfo.Texture, slot);

            // TODO: Pipepline and binding.
            commandBuffer->Record([registry, slot, &textureExtraInfo]() {
                ApplyMaterialTexture(textureExtraInfo, registry, slot);
            });
        }

        NCHECK(mesh.RenderHandle);
        commandBuffer->DrawIndexed(mesh.RenderHandle, mesh.Indices.size());
    }

}// namespace Nenuphar