#pragma once

#include "Nenuphar/Common/Type/Type.hpp"
#include "Nenuphar/Graphics/Mesh.hpp"
#include "Nenuphar/Rendering/CommandBuffer.hpp"
#include "Nenuphar/Rendering/UniformRegistry.hpp"


namespace Nenuphar
{

    struct Model
    {
        std::vector<Mesh> Meshes;
    };

    void RenderCommandSubmitModel(SharedRef<RenderDevice> device, Model& model);

    void RenderCommandDrawModel(SharedRef<CommandBuffer> commandBuffer,
                                SharedRef<UniformRegistry> registry,
                                const Model& model);

    Model CreateFloorModel();

    Model CreateCubeModel();

}// namespace Nenuphar