#pragma once

#include "Nenuphar/Common/Type/Type.hpp"
#include "Nenuphar/Entity/EntityRegistry.hpp"
#include "Nenuphar/Math/Vector4.hpp"
#include "Nenuphar/Model/Model.hpp"
#include "Nenuphar/Model/ModelAsset.hpp"
#include "Nenuphar/Rendering/RenderDevice.hpp"
#include "Nenuphar/Rendering/Texture.hpp"
#include "Nenuphar/Rendering/CommandQueue.hpp"


namespace Np = Nenuphar;

struct RenderableModel
{
    Np::Model Model;
};

struct Colorable
{
    Vector4f Color;
};

struct RenderableTexture
{
    Np::Texture Texture;
};

struct RenderTextures
{
    Np::Texture WallTexture;
};

struct RenderData
{
    static RenderData Create(SharedRef<Np::RenderDevice> device);

    void OnRenderData(SharedRef<Np::CommandQueue> commandQueue, Np::EntityRegistry& registry);

    SharedRef<Np::RenderDevice> Device;
    SharedRef<Np::ModelAsset> SponzaAsset;
};


static constexpr Vector4f GDefaultColor =
        Vector4f(
            36.0f / 255.0f, 
            36.0f / 255.0f, 
            36.0f / 255.0f, 
            255.0f / 255.0f);
