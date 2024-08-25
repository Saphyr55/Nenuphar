#include "Nenuphar/Model/TOL/TOLMeshLoader.hpp"
#include "Nenuphar/Common/Type/Result.hpp"
#include "Nenuphar/Core/IO/Path.hpp"
#include "Nenuphar/Core/Logger/Logger.hpp"
#include "Nenuphar/Rendering/Texture.hpp"
#include "Nenuphar/Rendering/Vertex.hpp"

#define TINYOBJLOADER_IMPLEMENTATION
#include <tiny_obj_loader.h>

#include <optional>
#include <vector>

namespace Nenuphar
{

    Result<Model, ModelLoaderError> TOLModelLoader::Load(const Path& path) const
    {
        using Res = Result<Model, ModelLoaderError>;

        if (!path.IsExists())
        {
            return Res(Res::kErrTag, ModelLoaderError::PathNotExist);
        }
        
        tinyobj::attrib_t attrib;
        std::vector<tinyobj::shape_t> shapes;
        std::vector<tinyobj::material_t> materials;

        std::string warn;
        std::string err;

        bool ret = tinyobj::LoadObj(&attrib,
                                    &shapes,
                                    &materials,
                                    &err,
                                    path.GetFilePath().c_str());

        if (!warn.empty())
        {
            NP_WARN(TOLModelLoader::Load, "On load obj file '{}', info:{}", path.GetFilePath(), warn);
        }

        if (!err.empty())
        {
            NP_ERROR(TOLModelLoader::Load, "On load obj file '{}'", path.GetFilePath());
            NP_ERROR(TOLModelLoader::Load, "TOL message : {}", err);
        }

        if (!ret)
        {
            NP_ERROR(TOLModelLoader::Load, "Impossible to parse the model from '{}'", path.GetFilePath());

            return Res(Res::kErrTag, ModelLoaderError::MalFormat);
        }

        NP_INFO(TOLModelLoader::Load, "Load the model from '{}'", path.GetFilePath());

        std::vector<Mesh> meshes;

        // Loop over shapes
        for (size_t s = 0; s < shapes.size(); s++)
        {
            std::vector<Vertex> vertices;
            std::vector<VIndice> indices;
            std::vector<Texture> textures;

            // Loop over faces(polygon)
            size_t index_offset = 0;
            for (size_t f = 0; f < shapes[s].mesh.num_face_vertices.size(); f++)
            {
                size_t fv = size_t(shapes[s].mesh.num_face_vertices[f]);
                
                // Loop over vertices in the face.
                for (size_t v = 0; v < fv; v++)
                {
                    // access to vertex
                    tinyobj::index_t idx = shapes[s].mesh.indices[index_offset + v];

                    tinyobj::real_t vx = attrib.vertices[3 * size_t(idx.vertex_index) + 0];
                    tinyobj::real_t vy = attrib.vertices[3 * size_t(idx.vertex_index) + 1];
                    tinyobj::real_t vz = attrib.vertices[3 * size_t(idx.vertex_index) + 2];

                    Vector3f pos(vx, vy, vz);
                    Vector3f normal;
                    Vector2f uv;

                    // Check if `normal_index` is zero or positive. negative = no normal data
                    if (idx.normal_index >= 0)
                    {
                        tinyobj::real_t nx = attrib.normals[3 * size_t(idx.normal_index) + 0];
                        tinyobj::real_t ny = attrib.normals[3 * size_t(idx.normal_index) + 1];
                        tinyobj::real_t nz = attrib.normals[3 * size_t(idx.normal_index) + 2];
                        normal = Vector3f(nx, ny, nz);
                    }

                    // Check if `texcoord_index` is zero or positive. negative = no texcoord data
                    if (idx.texcoord_index >= 0)
                    {
                        tinyobj::real_t tx = attrib.texcoords[2 * size_t(idx.texcoord_index) + 0];
                        tinyobj::real_t ty = attrib.texcoords[2 * size_t(idx.texcoord_index) + 1];
                        uv = Vector2f(tx, ty);
                    }

                    Vertex vertex(pos, normal, uv);
                    vertices.push_back(vertex);
                }

                VIndice indice(fv);
                Texture texture;

                index_offset += fv;

                // per-face material
                // shapes[s].mesh.material_ids[f];
            }

            Mesh mesh(vertices, indices, textures);
            meshes.push_back(mesh);
        }

        NP_INFO(TOLModelLoader::Load, "Finish to load the model from '{}'", path.GetFilePath());

        return Res(Res::kValTag, Model(meshes));
    }
}