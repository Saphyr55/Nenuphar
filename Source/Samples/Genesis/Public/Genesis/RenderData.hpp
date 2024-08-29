#pragma once

#include "Nenuphar/Common/Type/Type.hpp"
#include "Nenuphar/Entity/Entity.hpp"
#include "Nenuphar/Entity/EntityRegistry.hpp"
#include "Nenuphar/Model/Model.hpp"
#include "Nenuphar/Rendering/OpenGL/Uniform.hpp"
#include "Nenuphar/Rendering/Renderer.hpp"
#include "Nenuphar/Rendering/Shader.hpp"
#include "Nenuphar/Rendering/Texture.hpp"

namespace Np = Nenuphar;

struct RenderData
{
    static SharedRef<RenderData> Default();

    Np::ModelId BunnyModelId;
    Np::ModelId FloorModelId;
    Np::ModelId CubeModelId;
    Np::ModelId BarrelModelId;
    Np::Texture WallTexture;
    Np::UniquePtr<Np::Shader> Shader;
    Np::UniformRegistry Registry;
    Np::SharedRef<Np::Renderer> Renderer;
};

void OnRenderData(RenderData& data,
                  Np::EntityRegistry& registry,
                  Np::Entity floor,
                  Np::Entity bunny,
                  Np::Entity cube,
                  Np::Entity barrel);
