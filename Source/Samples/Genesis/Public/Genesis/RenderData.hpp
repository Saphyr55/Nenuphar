#pragma once

#include "Nenuphar/Common/Type/Type.hpp"
#include "Nenuphar/Entity/Entity.hpp"
#include "Nenuphar/Entity/EntityRegistry.hpp"
#include "Nenuphar/Math/Vector4.hpp"
#include "Nenuphar/Model/Model.hpp"
#include "Nenuphar/Rendering/OpenGL/Uniform.hpp"
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

struct RenderModels
{
    Np::ModelId CubeModelId;
    Np::ModelId SponzaModelId;
    Np::ModelId FloorModelId;
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
    using TRDefault = std::tuple<
        Np::SharedRef<RenderData>, 
        RenderModels, 
        RenderTextures>; 

    static TRDefault Default();

    Np::UniquePtr<Np::Shader> Shader;
    Np::UniformRegistry Registry;
    Np::SharedRef<Np::Renderer> Renderer;
};

void OnRenderData(RenderData& data, Np::EntityRegistry& registry);

static constexpr Vector4f GDefaultColor =
        Vector4f(
            36.0f / 255.0f, 
            36.0f / 255.0f, 
            36.0f / 255.0f, 
            255.0f / 255.0f);
