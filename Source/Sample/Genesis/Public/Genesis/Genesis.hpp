#pragma once

#include "Nenuphar/Core/Engine.hpp"

#include "Nenuphar/ApplicationCore/Window.hpp"

#include "Nenuphar/Math/Math.hpp"
#include "Nenuphar/Math/Camera.hpp"

#include "Nenuphar/Rendering/GraphicContext.hpp"
#include "Nenuphar/Rendering/OpenGL/OpenGLVertexArray.hpp"
#include "Nenuphar/Rendering/Texture.hpp"
#include "Nenuphar/Rendering/OpenGL/OpenGLShader.hpp"
#include "Nenuphar/Rendering/OpenGL/Uniform.hpp"

#include "Generated/Generated.hpp"

using namespace Nenuphar;

struct RenderData
{
    static Ptr<RenderData> New();

    Ptr<OpenGLVertexArray> VAO;
    Ptr<OpenGLVertexBuffer> VBO;
    TextureID WallTexture;
    Ptr<OpenGLShader> Program;
    Ptr<UniformRegistry> Registry;
};

struct Env
{
    static Env& New(Window& window);
    static void Init(Env& env);
    static void Render(Env& env);

    Env(UInt16 id, Ptr<GraphicContext> graphicContext, Window& window);
    ~Env() = default;

    UInt16 Id;
    Ptr<GraphicContext> MainGraphicContext;
    Ptr<RenderData> MainRenderData;
    Window& MainWindow;
    OrbitCamera MainCamera;
    Float CameraVelocity = 0.005f;
};


static thread_local std::unordered_map<UInt16, Ptr<Env>> EnvRegistry;

