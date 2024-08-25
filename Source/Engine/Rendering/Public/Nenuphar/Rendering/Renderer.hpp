#pragma once

#include "Nenuphar/Model/Model.hpp"
#include "Nenuphar/Rendering/Mesh.hpp"
#include "Nenuphar/Rendering/Shader.hpp"


namespace Nenuphar
{

    class Renderer
    {
    public:
        virtual ModelId PersistModel(const Model& model) const = 0;

        virtual MeshId PersistMesh(const Mesh& mesh) const = 0;

        virtual void DrawModel(const Shader& shader, const ModelId& model) const = 0;

        virtual void DrawMesh(const Shader& shader,
                              const MeshId& mesh) const = 0;

    };  

}

