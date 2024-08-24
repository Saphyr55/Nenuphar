#pragma once

#include "Nenuphar/Rendering/OpenGL/Vertex.hpp"

namespace Nenuphar 
{
    
    class WavefrontObjStmt
    {
    public:
        virtual ~WavefrontObjStmt() = default;
    };
    
    class VertexStmt : public WavefrontObjStmt
    {
        
    };

}