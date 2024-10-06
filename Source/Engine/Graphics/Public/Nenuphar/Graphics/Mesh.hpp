#pragma once

#include "Nenuphar/Common/Type/Type.hpp"
#include "Nenuphar/Graphics/Material.hpp"
#include "Nenuphar/Rendering/RenderHandle.hpp"
#include "Nenuphar/Rendering/Vertex.hpp"

#include <vector>

namespace Nenuphar
{
    class RenderDevice;
    class CommandBuffer;
    class UniformRegistry;

    class Mesh : public RenderHandle
    {
    public:
        std::vector<Vertex> Vertices;
        std::vector<VIndice> Indices;
        std::vector<Material> Materials;
        SharedRef<RenderHandle> RenderHandle;

        virtual void Destroy() override;

        Mesh(const std::vector<Vertex>& vertices,
             const std::vector<VIndice>& indices,
             const std::vector<Material>& materials)
            : Vertices(vertices)
            , Indices(indices)
            , Materials(materials)
        {
        }
    };

    void RenderCommandSubmitMesh(SharedRef<RenderDevice> renderDevice, Mesh& mesh);

    void RenderCommandDrawMesh(SharedRef<CommandBuffer> commandBuffer,
                               SharedRef<UniformRegistry> registry,
                               const Mesh& mesh);

}// namespace Nenuphar