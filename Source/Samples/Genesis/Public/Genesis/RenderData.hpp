#pragma once

#include "Nenuphar/Common/Type/Type.hpp"
#include "Nenuphar/Entity/EntityRegistry.hpp"
#include "Nenuphar/Math/Vector4.hpp"
#include "Nenuphar/Model/Model.hpp"
#include "Nenuphar/Rendering/Renderer.hpp"
#include "Nenuphar/Rendering/Shader.hpp"
#include "Nenuphar/Rendering/Texture.hpp"

namespace Np = Nenuphar;

struct RenderableModel
{
    Np::ModelId Model;
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
    static RenderData Create();

    void OnRenderData(Np::EntityRegistry& registry);

    Np::ModelId BarrelModelId;
    Np::ModelId SponzaModelId;
    Np::ModelId FloorModelId;
};


static constexpr Vector4f GDefaultColor =
        Vector4f(
            36.0f / 255.0f, 
            36.0f / 255.0f, 
            36.0f / 255.0f, 
            255.0f / 255.0f);
