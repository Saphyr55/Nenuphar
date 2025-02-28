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

    struct Mesh : public RenderHandle
    {
    public:
        std::vector<Vertex> Vertices;
        std::vector<VIndice> Indices;
        std::vector<Material> Materials;
        std::vector<std::size_t> FaceOffsets; 
        SharedRef<RenderHandle> RenderHandle;
    
    public:
        virtual void Destroy() override;

        Mesh(const std::vector<Vertex>& vertices,
             const std::vector<VIndice>& indices,
             const std::vector<Material>& materials,
             const std::vector<std::size_t>& faceOffsets)
            : Vertices(vertices)
            , Indices(indices)
            , FaceOffsets(faceOffsets)
            , Materials(materials)
        {
        }

        Mesh(const Mesh&) = default;
        Mesh(Mesh&&) = default;
        ~Mesh() = default;

    };

    void RenderCommandSubmitMesh(SharedRef<RenderDevice> renderDevice, Mesh& mesh);

    void RenderCommandDrawMesh(SharedRef<CommandBuffer> commandBuffer,
                               SharedRef<UniformRegistry> registry,
                               const Mesh& mesh);

}// namespace Nenuphar