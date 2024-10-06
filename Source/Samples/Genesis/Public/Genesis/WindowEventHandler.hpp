#pragma once

#include "Nenuphar/ApplicationCore/Window.hpp"
#include "Nenuphar/Common/Type/Type.hpp"
#include "Nenuphar/EventSystem/Signal.hpp"
#include "Nenuphar/InputSystem/Event.hpp"


#define NP_DEFINE_SIGNAL(Type, Attr)                                           \
public:                                                                        \
    ::Nenuphar::Connection<Type> Add##Attr(auto&& delegate) const              \
    {                                                                          \
        return m_on##Attr.Connect(std::forward<decltype(delegate)>(delegate)); \
    }                                                                          \
    void Emit##Attr(auto&&... values) const                                    \
    {                                                                          \
        m_on##Attr.Emit(std::forward<decltype(values)...>(values)...);         \
    }                                                                          \
    ::Nenuphar::Signal<Type>& Attr() const                                     \
    {                                                                          \
        return m_on##Attr;                                                     \
    }                                                                          \
                                                                               \
private:                                                                       \
    mutable ::Nenuphar::Signal<Type> m_on##Attr;

namespace Np = Nenuphar;

namespace Nenuphar
{
    struct ResizeEvent
    {
        SharedRef<Window> Window;
        UInt Width;
        UInt Height;
    };

    struct CloseEvent
    {
        SharedRef<Window> Window;
    };

}// namespace Nenuphar

class WindowEventHandler
{
public:
    NP_DEFINE_SIGNAL(const Np::CloseEvent&, OnClose)
    NP_DEFINE_SIGNAL(const Np::ResizeEvent&, OnResize)
    NP_DEFINE_SIGNAL(const Np::MouseWheelEvent&, OnMouseWheel)
    NP_DEFINE_SIGNAL(const Np::MouseButtonEvent&, OnButtonDown)
    NP_DEFINE_SIGNAL(const Np::MouseButtonEvent&, OnButtonUp)
    NP_DEFINE_SIGNAL(const Np::MouseMoveEvent&, OnMouseMove)
    NP_DEFINE_SIGNAL(const Np::KeyEvent&, OnKeyDown)
    NP_DEFINE_SIGNAL(const Np::KeyEvent&, OnKeyRelease)
    NP_DEFINE_SIGNAL(const Np::KeyEvent&, OnKeyPressed)

public:
    WindowEventHandler()
        : m_window(nullptr)
    {
    }

    inline void SetWindow(Np::SharedRef<Np::Window> window)
    {
        m_window = window;
    }

    inline Np::SharedRef<Np::Window> GetWindow()
    {
        return m_window;
    }

private:
    Np::SharedRef<Np::Window> m_window;
};
