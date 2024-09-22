#include "Nenuphar/Model/Model.hpp"
#include "Nenuphar/Graphics/Mesh.hpp"


namespace Nenuphar
{
    
    void RenderCommandSubmitModel(SharedRef<RenderDevice> device, Model& model)
    {
        for (auto& mesh: model.Meshes)
        {
            RenderCommandSubmitMesh(device, mesh);
        }
    }

    void RenderCommandDrawModel(SharedRef<CommandBuffer> commandBuffer,
                            SharedRef<UniformRegistry> registry,
                            const Model& model)
    {
        for (auto& mesh: model.Meshes)
        {
            RenderCommandDrawMesh(commandBuffer, registry, mesh);
        }
    }

    Model CreateFloorModel()
    {

        const std::vector<Vertex> Vertices{
                Vertex{Vector3f(-1.0f, 0.0f, 1.0f), Vector3f(1.0f, 1.0f, 1.0f), Vector2f(0.0f, 0.0f)},
                Vertex{Vector3f(-1.0f, 0.0f, -1.0f), Vector3f(1.0f, 1.0f, 1.0f), Vector2f(0.0f, 1.0f)},
                Vertex{Vector3f(1.0f, 0.0f, -1.0f), Vector3f(1.0f, 1.0f, 1.0f), Vector2f(1.0f, 1.0f)},
                Vertex{Vector3f(1.0f, 0.0f, 1.0f), Vector3f(1.0f, 1.0f, 1.0f), Vector2f(1.0f, 0.0f)}};

        // Indices for vertices order
        std::vector<VIndice> Indices{0, 1, 2,
                                     0, 2, 3};

        return Model({Mesh(std::move(Vertices), std::move(Indices), {})});
    };

    Model CreateCubeModel()
    {
        const std::vector<Vertex> CubeVertices{
                Vertex(Vector3f(0.5f, 0.5f, 0.5f), Vector3f(1.0f), Vector2f(0.0f, 0.0f)),
                Vertex(Vector3f(-0.5f, 0.5f, -0.5f), Vector3f(1.0f), Vector2f(0.0f, 1.0f)),
                Vertex(Vector3f(-0.5f, 0.5f, 0.5f), Vector3f(1.0f), Vector2f(1.0f, 0.0f)),
                Vertex(Vector3f(0.5f, -0.5f, -0.5f), Vector3f(1.0f), Vector2f(1.0f, 1.0f)),
                Vertex(Vector3f(-0.5f, -0.5f, -0.5f), Vector3f(1.0f), Vector2f(0.0f, 0.0f)),
                Vertex(Vector3f(0.5f, 0.5f, -0.5f), Vector3f(1.0f), Vector2f(1.0f, 0.0f)),
                Vertex(Vector3f(0.5f, -0.5f, 0.5f), Vector3f(1.0f), Vector2f(0.0f, 1.0f)),
                Vertex(Vector3f(-0.5f, -0.5f, 0.5f), Vector3f(1.0f), Vector2f(1.0f, 1.0f))};

        const std::vector<VIndice> CubeIndices{
                0, 1, 2,
                1, 3, 4,
                5, 6, 3,
                7, 3, 6,
                2, 4, 7,
                0, 7, 6,
                0, 5, 1,
                1, 5, 3,
                5, 0, 6,
                7, 4, 3,
                2, 1, 4,
                0, 2, 7};

        return Model({Mesh(std::move(CubeVertices), std::move(CubeIndices), {})});
    };

}// namespace Nenuphar