#pragma once

#include "Nenuphar/Common/Type/Type.hpp"
#include "Nenuphar/Entity/EntityRegistry.hpp"
#include "Nenuphar/Model/Model.hpp"
#include "Nenuphar/Rendering/OpenGL/OpenGLTexture.hpp"
#include "Nenuphar/Rendering/OpenGL/Uniform.hpp"
#include "Nenuphar/Rendering/Renderer.hpp"
#include "Nenuphar/Rendering/Shader.hpp"

namespace Np = Nenuphar;

struct RenderData
{
    static SharedRef<RenderData> Default();

    Np::ModelId BunnyModelId;
    Np::ModelId FloorModelId;
    Np::ModelId CubeModelId;
    SharedRef<Np::OpenGLTexture2D> WallTexture;
    UniquePtr<Np::Shader> Shader;
    UniquePtr<Np::UniformRegistry> Registry;
    UniquePtr<Np::Renderer> Renderer;
};


void OnRenderData(RenderData& data,
                  Np::EntityRegistry& registry,
                  Np::Entity floor,
                  Np::Entity bunny,
                  Np::Entity cube);
