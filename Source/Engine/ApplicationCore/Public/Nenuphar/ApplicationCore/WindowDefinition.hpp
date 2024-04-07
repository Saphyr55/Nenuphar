#pragma once

#include "Nenuphar/Common/Type/Type.hpp"
#include "Nenuphar/EventSystem/Signal.hpp"
#include "Nenuphar/EventSystem/Event.hpp"
#include "Nenuphar/InputSystem/Event.hpp"

#define NP_DEFINE_SIGNAL(Type, Attr) \
public:                            \
Connection<Type> Add##Attr(auto&& delegate) const \
{ \
    return m_on##Attr.Connect(std::forward<decltype(delegate)>(delegate)); \
}                                    \
void Emit##Attr(auto&&... values) const \
{ \
    m_on##Attr.Emit(std::forward<decltype(values)...>(values)...); \
}                                    \
Signal<Type>& Attr() const { return m_on##Attr; } \
private : \
mutable Signal<Type> m_on##Attr;

namespace Nenuphar
{

    struct WindowDefinition
    {
        String Title;
        Float Width;
        Float Height;
    };

    class WindowSignals
    {
        NP_DEFINE_SIGNAL(const CloseEvent&      , OnClose)
        NP_DEFINE_SIGNAL(const ResizeEvent&     , OnResize)
        NP_DEFINE_SIGNAL(const MouseWheelEvent& , OnMouseWheel)
        NP_DEFINE_SIGNAL(const MouseButtonEvent&, OnButtonPressed)
        NP_DEFINE_SIGNAL(const MouseButtonEvent&, OnButtonRelease)
        NP_DEFINE_SIGNAL(const MouseMoveEvent&  , OnMouseMove)
        NP_DEFINE_SIGNAL(const KeyEvent&        , OnKeyDown)
        NP_DEFINE_SIGNAL(const KeyEvent&        , OnKeyRelease)
        NP_DEFINE_SIGNAL(const KeyEvent&        , OnKeyPressed)
    };

}