#pragma once

#include "Nenuphar/Core/Engine.hpp"
#include "Nenuphar/Graphics/GraphicContext.hpp"
#include "Nenuphar/ApplicationCore/Window.hpp"
#include "Nenuphar/Math/Camera.hpp"
#include "Nenuphar/Math/Math.hpp"

#include "Generated/Generated.hpp"

using namespace Nenuphar;

struct Env
{

    static Env& New(Window& window);
    static void Init(Env& env);
    static void Render(Env& env);

    Env(UInt16 id, Ptr<GraphicContext> graphicContext, Window& window);

    UInt16 Id;
    Ptr<GraphicContext> MainGraphicContext;
    Window& MainWindow;
    OrbitCamera MainCamera;
};


static thread_local std::unordered_map<UInt16, Ptr<Env>> EnvRegistry;
