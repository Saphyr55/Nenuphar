#pragma once

#include "Nenuphar/ApplicationCore/Window.hpp"
#include "Nenuphar/Core/Engine.hpp"
#include "Nenuphar/ApplicationCore/WindowDefinition.hpp"
#include "Nenuphar/Common/Type/Type.hpp"
#include "Nenuphar/Entity/Entity.hpp"
#include "Nenuphar/Math/Camera.hpp"

#include "Nenuphar/Entity/EntityRegistry.hpp"
#include "Nenuphar/Rendering/GraphicContext.hpp"
#include "Nenuphar/Rendering/OpenGL/OpenGLShader.hpp"
#include "Nenuphar/Rendering/OpenGL/OpenGLTexture.hpp"
#include "Nenuphar/Rendering/OpenGL/OpenGLVertexArray.hpp"
#include "Nenuphar/Rendering/OpenGL/Uniform.hpp"
#include "Nenuphar/Rendering/Texture.hpp"


namespace Np = Nenuphar;

namespace gn
{

    struct RenderData
    {
        static SharedRef<RenderData> Default();

        UniquePtr<Np::OpenGLVertexArray> VAO;
        UniquePtr<Np::OpenGLVertexBuffer> VBO;
        Np::OpenGLTexture2D WallTexture;
        UniquePtr<Np::OpenGLShader> ShaderProgram;
        UniquePtr<Np::UniformRegistry> Registry;
    };

    class GenesisApp
    {
    public:
        void Init();
        void Render();

    private:
        void ResetCameraTarget(const Np::KeyEvent& evt, Np::OrbitCamera& camera);
        void OnMoveCameraXY(const Np::MouseMoveEvent& evt, Np::OrbitCamera& camera);
        void OnRotateCamera(const Np::MouseMoveEvent& evt, Np::OrbitCamera& camera);
        void OnMoveCameraZOnScroll(const Np::MouseWheelEvent& evt, Np::OrbitCamera& camera);

    public:
        GenesisApp();
        ~GenesisApp() = default;

    private:
        Np::EntityRegistry m_registry;
        Np::Entity MainCamera;
        UniquePtr<Np::GraphicContext> MainGraphicContext;
        SharedRef<Np::Window> MainWindow;
        SharedRef<RenderData> MainRenderData;
        float CameraVelocity = 0.005f;
    };

}


