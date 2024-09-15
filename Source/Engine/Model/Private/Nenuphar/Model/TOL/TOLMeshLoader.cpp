#include "Nenuphar/Model/TOL/TOLMeshLoader.hpp"
#include "Nenuphar/Asset/AssetRegistry.hpp"
#include "Nenuphar/Common/Instanciate.hpp"
#include "Nenuphar/Common/Type/Result.hpp"
#include "Nenuphar/Core/Debug.hpp"
#include "Nenuphar/Core/IO/Path.hpp"
#include "Nenuphar/Core/Logger/Logger.hpp"
#include "Nenuphar/Math/Vector3.hpp"
#include "Nenuphar/Model/ModelAsset.hpp"
#include "Nenuphar/Rendering/Texture.hpp"
#include "Nenuphar/Rendering/TextureAsset.hpp"
#include "Nenuphar/Rendering/Vertex.hpp"
#include <algorithm>

#define TINYOBJLOADER_IMPLEMENTATION
#define TINYOBJLOADER_USE_MAPBOX_EARCUT
#include <tiny_obj_loader.h>

#include <optional>
#include <vector>


namespace Nenuphar
{

    ModelLoader::TRes TOLModelLoader::Load(const Path& path,
                                           const TOLModelAssetOptions& options) const
    {
        using TRes = ModelLoader::TRes;
        AssetRegistry& assetRegistry = AssetRegistry::Instance();

        NP_INFO(TOLModelLoader::Load, "Load the model from '{}'", path.GetFilePath());

        if (!path.IsExists())
        {
            return TRes(TRes::kErrTag, ModelLoaderError::PathNotExist);
        }

        auto mtlPathDir = options.MtlPathDir;

        tinyobj::attrib_t attrib;
        std::vector<tinyobj::shape_t> shapes;
        std::vector<tinyobj::material_t> materials;

        std::string warn;
        std::string err;

        bool ret = tinyobj::LoadObj(&attrib,
                                    &shapes,
                                    &materials,
                                    &err,
                                    path.GetFilePath().c_str(),
                                    mtlPathDir.has_value()
                                            ? mtlPathDir->GetFilePath().c_str()
                                            : nullptr);

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

            return TRes(TRes::kErrTag, ModelLoaderError::MalFormat);
        }

        std::vector<Mesh> meshes;
        std::map<std::string, Texture> texturesMapping;

        for (const tinyobj::material_t& material: materials)
        {
            if (material.diffuse_texname.length() > 0)
            {
                std::string pathTexture = mtlPathDir->GetFilePath() + material.diffuse_texname;

                if (!texturesMapping.contains(pathTexture) && options.PersistTexture && options.Renderer)
                {
                    AssetOptions texAssetOptions;
                    texAssetOptions.IsFromAsset = false;
                    SharedRef<TextureAsset> textureAsset = assetRegistry.Load<TextureAsset>(pathTexture, texAssetOptions);
                    NCHECK(textureAsset)

                    Texture texture = options.Renderer->PersistTexture(textureAsset);
                    texturesMapping.insert({pathTexture, texture});
                }
            }
        }

        // Loop over shapes
        for (const tinyobj::shape_t& shape: shapes)
        {
            const tinyobj::mesh_t& mesh = shape.mesh;

            std::vector<Vertex> vertices;
            std::vector<VIndice> indices;
            std::vector<Texture> textures;

            // Loop over faces(polygon)
            std::size_t index_offset = 0;
            for (std::size_t f = 0; f < mesh.num_face_vertices.size(); f++)
            {
                std::size_t fv = size_t(mesh.num_face_vertices[f]);

                // Loop over vertices in the face.
                for (std::size_t v = 0; v < fv; v++)
                {
                    // access to vertex
                    tinyobj::index_t idx = mesh.indices[index_offset + v];

                    tinyobj::real_t vx = attrib.vertices[3 * std::size_t(idx.vertex_index) + 0];
                    tinyobj::real_t vy = attrib.vertices[3 * std::size_t(idx.vertex_index) + 1];
                    tinyobj::real_t vz = attrib.vertices[3 * std::size_t(idx.vertex_index) + 2];

                    Vector3f pos(vx, vy, vz);
                    Vector3f normal;
                    Vector2f uv;

                    // Check if `normal_index` is zero or positive. negative = no normal data
                    if (idx.normal_index >= 0)
                    {
                        tinyobj::real_t nx = attrib.normals[3 * std::size_t(idx.normal_index) + 0];
                        tinyobj::real_t ny = attrib.normals[3 * std::size_t(idx.normal_index) + 1];
                        tinyobj::real_t nz = attrib.normals[3 * std::size_t(idx.normal_index) + 2];
                        normal = Vector3f(nx, ny, nz);
                        normal = Vector3f::Normalize(normal);
                    }

                    // Check if `texcoord_index` is zero or positive. negative = no texcoord data
                    if (idx.texcoord_index >= 0)
                    {
                        tinyobj::real_t tx = attrib.texcoords[2 * std::size_t(idx.texcoord_index) + 0];
                        tinyobj::real_t ty = attrib.texcoords[2 * std::size_t(idx.texcoord_index) + 1];
                        uv = Vector2f(tx, ty);
                    }

                    Vertex vertex(pos, normal, uv);
                    vertices.push_back(vertex);
                    indices.push_back(indices.size());
                }

                index_offset += fv;

                // per-face material
                int m = mesh.material_ids.at(f);
                if (m < 0)
                {
                    continue;
                }

                tinyobj::material_t& material = materials.at(m);
                std::string pathTexture = mtlPathDir->GetFilePath() + material.diffuse_texname;
                if (texturesMapping.contains(pathTexture))
                {
                    if (std::find(textures.begin(), textures.end(), texturesMapping.at(pathTexture)) == textures.end())
                    {
                        textures.push_back(texturesMapping.at(pathTexture));
                    }
                }

            }

            meshes.push_back(Mesh(
                    std::move(vertices),
                    std::move(indices),
                    std::move(textures)));
        }


        NP_INFO(TOLModelLoader::Load, "Finish to load the model from '{}'", path.GetFilePath());

        return TRes(TRes::kValTag, Model(meshes));
    }
}// namespace Nenuphar