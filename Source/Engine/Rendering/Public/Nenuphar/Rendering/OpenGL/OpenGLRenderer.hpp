#pragma once

#include "Nenuphar/Rendering/Renderer.hpp"

namespace Nenuphar
{
    
    class OpenGLRenderer : public Renderer
    {
    public:
        virtual ModelId PersistModel(const Model& model) const override;

        virtual MeshId PersistMesh(const Mesh& mesh) const override;

        virtual void DrawMesh(const Shader& shader, const MeshId& mesh) const override;
    };

}