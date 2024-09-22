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

    struct Mesh
    {
        std::vector<Vertex> Vertices;
        std::vector<VIndice> Indices;
        std::vector<Material> Materials;
        SharedRef<RenderHandle> RenderHandle;
    };

    void RenderCommandSubmitMesh(SharedRef<RenderDevice> renderDevice, Mesh& mesh);

    void RenderCommandDrawMesh(SharedRef<CommandBuffer> commandBuffer,
                           SharedRef<UniformRegistry> registry,
                           const Mesh& mesh);

}// namespace Nenuphar