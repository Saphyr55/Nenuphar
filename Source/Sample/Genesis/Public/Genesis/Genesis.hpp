#pragma once

#include "Nenuphar/ApplicationCore/WindowInterface.hpp"
#include "Nenuphar/Core/Engine.hpp"
#include "Nenuphar/ApplicationCore/WindowDefinition.hpp"
#include "Nenuphar/Common/Type/Type.hpp"
#include "Nenuphar/Math/Camera.hpp"

#include "Nenuphar/Rendering/GraphicContext.hpp"
#include "Nenuphar/Rendering/OpenGL/OpenGLVertexArray.hpp"
#include "Nenuphar/Rendering/Texture.hpp"
#include "Nenuphar/Rendering/OpenGL/OpenGLShader.hpp"
#include "Nenuphar/Rendering/OpenGL/Uniform.hpp"

namespace Np = Nenuphar;

namespace gn
{

    struct RenderData
    {
        static SharedRef<RenderData> Default();

        UniquePtr<Np::OpenGLVertexArray> VAO;
        UniquePtr<Np::OpenGLVertexBuffer> VBO;
        Np::TextureID WallTexture;
        UniquePtr<Np::OpenGLShader> ShaderProgram;
        UniquePtr<Np::UniformRegistry> Registry;
    };

    class GenesisApp
    {
    public:
        void Init();
        void Render();

    private:
        void ResetCameraTarget(const Np::KeyEvent& evt);
        void OnMoveCameraXY(const Np::MouseMoveEvent& evt);
        void OnRotateCamera(const Np::MouseMoveEvent& evt);
        void OnMoveCameraZOnScroll(const Np::MouseWheelEvent& evt);

    public:
        GenesisApp();
        ~GenesisApp() = default;

    private:
        UniquePtr<Np::GraphicContext> MainGraphicContext;
        SharedRef<Np::WindowInterface> MainWindow;
        SharedRef<RenderData> MainRenderData;
        Np::OrbitCamera MainCamera;
        float CameraVelocity = 0.005f;
    };

}


