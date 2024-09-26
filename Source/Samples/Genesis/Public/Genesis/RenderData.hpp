#pragma once

#include "Nenuphar/Common/Type/Type.hpp"
#include "Nenuphar/Entity/EntityRegistry.hpp"
#include "Nenuphar/Math/Vector4.hpp"
#include "Nenuphar/Model/Model.hpp"
#include "Nenuphar/Model/ModelAsset.hpp"
#include "Nenuphar/Rendering/RenderDevice.hpp"


namespace Np = Nenuphar;

struct RenderableModel
{
    Np::Model* Model = nullptr;
};

struct Colorable
{
    Vector4f Color;
};


struct RenderData
{
    static RenderData Create(SharedRef<Np::RenderDevice> device);

    void OnRenderData(SharedRef<Np::CommandBuffer> commandBuffer, Np::EntityRegistry& registry);

    SharedRef<Np::RenderDevice> Device;
    SharedRef<Np::ModelAsset> SponzaAsset;
};


static constexpr Vector4f GDefaultColor =
        Vector4f(
            36.0f / 255.0f, 
            36.0f / 255.0f, 
            36.0f / 255.0f, 
            255.0f / 255.0f);
