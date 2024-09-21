#include "Nenuphar/Rendering/Windows/WGLContext.hpp"
#include "Nenuphar/Core/Debug.hpp"
#include <memory>

#if NP_PLATFORM_WINDOWS

#include "Nenuphar/Core/Logger/Logger.hpp"
#include "Nenuphar/Rendering/Renderer.hpp"
#include "Nenuphar/Rendering/OpenGL/OpenGLDebugger.hpp"
#include "Nenuphar/Rendering/OpenGL/OpenGL.hpp"

#include <glad/glad.h>

namespace Nenuphar
{
    
    UniquePtr<GraphicsContext> GraphicsContext::Create(RenderAPI api, SharedRef<Window> window)
    {
        NCHECK(window);
        switch (api) 
        {
            case RenderAPI::OpenGL: {  
                WGLContext::Init();
                auto ww = std::reinterpret_pointer_cast<WindowsWindow>(window);
                auto deviceContext  = MakeUnique<WindowsDeviceContext>(ww);
                return MakeUnique<WGLContext>(std::move(deviceContext));
            }
            default: {
                NCHECK(false)
                return nullptr;
            }
        }
    }

    WGLContext::WGLContext(Ptr<WindowsDeviceContext> deviceContext)
        : m_deviceContext(std::move(deviceContext))
        , m_context(nullptr)
    {

        HDC handler = m_deviceContext->GetHDC();
        Int pixelFormatAttributes[] =
        {
            WGL_DRAW_TO_WINDOW_ARB, GL_TRUE,
            WGL_SUPPORT_OPENGL_ARB, GL_TRUE,
            WGL_DOUBLE_BUFFER_ARB,  GL_TRUE,
            WGL_ACCELERATION_ARB,   WGL_FULL_ACCELERATION_ARB,
            WGL_PIXEL_TYPE_ARB,     WGL_TYPE_RGBA_ARB,
            WGL_COLOR_BITS_ARB,     32,
            WGL_DEPTH_BITS_ARB,     24,
            WGL_STENCIL_BITS_ARB,   8,
            0
        };

        Int pixelFormat = 0;
        UInt numFormats = 0;
        wglChoosePixelFormatARB
        (
            handler,
            pixelFormatAttributes,
            nullptr,
            1,
            &pixelFormat,
            &numFormats
        );

        PIXELFORMATDESCRIPTOR pixelFormatDesc = {};
        {
            DescribePixelFormat
            (
                handler,
                pixelFormat,
                sizeof(PIXELFORMATDESCRIPTOR),
                &pixelFormatDesc
            );
            SetPixelFormat
            (
                handler,
                pixelFormat,
                &pixelFormatDesc
            );
        }

        Int majorVersion = 4;
        Int minorVersion = 6;

        Int openGLAttributes[] =
        {
            WGL_CONTEXT_MAJOR_VERSION_ARB,
            majorVersion,
            WGL_CONTEXT_MINOR_VERSION_ARB,
            minorVersion,
#if defined(_DEBUG) || defined(DEBUG)
            WGL_CONTEXT_FLAGS_ARB,
            WGL_CONTEXT_DEBUG_BIT_ARB,
#endif
            WGL_CONTEXT_PROFILE_MASK_ARB,
            WGL_CONTEXT_CORE_PROFILE_BIT_ARB,
            0
        };

        m_context = wglCreateContextAttribsARB(handler, 0, openGLAttributes);

        if (!m_context)
        {
            NP_ERROR(WGLContext::New, "Failed to create WGL Context.");
            throw std::runtime_error("");
        }

        Current();
        
        NP_INFO(WGLContext::WGLContext, "Setup WGL context.");

#if defined(_DEBUG) || defined(DEBUG)
        
        int contextFlags = 0;
        glGetIntegerv(GL_CONTEXT_FLAGS, &contextFlags);

        if (contextFlags & GL_CONTEXT_FLAG_DEBUG_BIT)
        {
            OpenGLInitDebugger();
            NP_INFO(WGLContext::WGLContext, "WGL context was setup in debug mode.");
        }
        else
        {
            NP_ERROR(WGLContext::WGLContext, "Failed to setup WGL context in debug mode.");
        }
#endif
    }

    WGLContext::~WGLContext()
    {
        wglDeleteContext(m_context);
        m_deviceContext->Release();
    }

    Void WGLContext::Init()
    {
        auto appName = TEXT("NenupharDummyApplication");

        WNDCLASSEX windowClass = {};
        windowClass.style = CS_OWNDC;
        windowClass.lpfnWndProc = DefWindowProcA;
        windowClass.lpszClassName = appName;
        windowClass.cbSize = sizeof(WNDCLASSEX);

        auto classId = RegisterClassEx(&windowClass);

        HWND dummyWindow = CreateWindowEx
        (
            0,
            MAKEINTATOM(classId),
            appName,
            0,
            CW_USEDEFAULT,
            CW_USEDEFAULT,
            CW_USEDEFAULT,
            CW_USEDEFAULT,
            0,
            0,
            windowClass.hInstance,
            0
        );

        HDC dummyDC = GetDC(dummyWindow);

        PIXELFORMATDESCRIPTOR pfd = {};
        pfd.nSize = sizeof(pfd);
        pfd.nVersion = 1;
        pfd.dwFlags =
            PFD_DRAW_TO_WINDOW | 
            PFD_SUPPORT_OPENGL | 
            PFD_DOUBLEBUFFER   ;
        pfd.iLayerType = PFD_MAIN_PLANE;
        pfd.iPixelType = PFD_TYPE_RGBA;
        pfd.cAlphaBits = 8;
        pfd.cColorBits = 32;
        pfd.cDepthBits = 24;
        pfd.cStencilBits = 8;

        Int pixelFormat = ChoosePixelFormat(dummyDC, &pfd);
        SetPixelFormat(dummyDC, pixelFormat, &pfd);

        HGLRC dummyContext = wglCreateContext(dummyDC);
        if (!dummyContext)
        {
            NP_ERROR(WGLContext::Init, "Failed to create WGL Context.");
            throw std::exception();
        }

        if (!wglMakeCurrent(dummyDC, dummyContext))
        {
            NP_ERROR(WGLContext::Init, "Failed to make WGL Context current.");
            throw std::exception();
        }

        if (!gladLoadWGL(dummyDC))
        {
            throw std::runtime_error("Failed to load WGL.");
        }

        if (!gladLoadGL())
        {
            throw std::runtime_error("Failed to load OpenGL with glad.");
        }

        auto msg = String((const char*)glGetString(GL_VERSION));
        NP_INFO(WGLContext::Init, "OpenGL was loaded successfuly.");
        NP_INFO(WGLContext::Init, "OpenGL Verion : '{}'", msg);

        wglMakeCurrent(dummyDC, 0);
        wglDeleteContext(dummyContext);
        ReleaseDC(dummyWindow, dummyDC);
        DestroyWindow(dummyWindow);
    }

    void WGLContext::Current() const
    {
        wglMakeCurrent(m_deviceContext->GetHDC(), m_context);
    }

    void WGLContext::SwapBuffers() const
    {
        wglSwapLayerBuffers(m_deviceContext->GetHDC(), WGL_SWAP_MAIN_PLANE);
    }

}

#endif