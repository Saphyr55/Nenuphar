#include "Nenuphar/Model/TOL/TOLMeshLoader.hpp"

#include "Nenuphar/Asset/AssetRegistry.hpp"

#include "Nenuphar/Common/Type/Type.hpp"

#include "Nenuphar/Core/Debug.hpp"
#include "Nenuphar/Core/IO/Path.hpp"
#include "Nenuphar/Core/Logger/Logger.hpp"

#include "Nenuphar/Graphics/Material.hpp"

#include "Nenuphar/Math/Vector3.hpp"

#include "Nenuphar/Model/ModelAsset.hpp"

#include "Nenuphar/Rendering/ImageAsset.hpp"
#include "Nenuphar/Rendering/RenderDevice.hpp"
#include "Nenuphar/Rendering/Texture.hpp"
#include "Nenuphar/Rendering/Vertex.hpp"

#define TINYOBJLOADER_IMPLEMENTATION
#include <tiny_obj_loader.h>

#include <optional>
#include <unordered_map>
#include <unordered_set>
#include <vector>


namespace Nenuphar
{

    ModelLoader::TRes TOLModelLoader::Load(const Path& path,
                                           const TOLModelAssetOptions& options) const
    {
        using TRes = ModelLoader::TRes;
        AssetRegistry& assets = AssetRegistry::Instance();
        bool toSubmit = options.IsSubmit && options.RenderDevice;
        
        NP_INFO(TOLModelLoader::Load, "Loading the obj file '{}'", path.GetFilePath());

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
            NP_WARN(TOLModelLoader::Load, "When loading the obj file '{}', info:{}", path.GetFilePath(), warn);
        }

        if (!err.empty())
        {
            NP_ERROR(TOLModelLoader::Load, "When loading the obj file '{}'", path.GetFilePath());
            NP_ERROR(TOLModelLoader::Load, "TOL message : {}", err);
        }

        if (!ret)
        {
            NP_ERROR(TOLModelLoader::Load, "Unable to parse the obj file '{}'", path.GetFilePath());

            return TRes(TRes::kErrTag, ModelLoaderError::MalFormat);
        }

        std::vector<Mesh> meshes;
        std::unordered_map<std::string, SharedRef<Texture>> texturesMapping;
        std::vector<Material> inMaterials;

        ImageAssetOptions imageOptions;
        imageOptions.IsFromAsset = false;
        
        TextureConstructOptions textureConstructOptions;
        textureConstructOptions.AutoRelease = options.AutoReleaseTextue;

        for (const tinyobj::material_t& m: materials)
        {
            Material material;
            material.Diffuse = Vector3f(m.diffuse[0], m.diffuse[1], m.diffuse[2]);
            material.Specular = Vector3f(m.specular[0], m.specular[1], m.specular[2]);
            material.Shininess = m.shininess;
            
            if (m.diffuse_texname.length() > 0)
            {
                std::string v = mtlPathDir->GetFilePath() + m.diffuse_texname;

                if (!texturesMapping.contains(v) && toSubmit)
                {
                    SharedRef<ImageAsset> image = assets.Load<ImageAsset>(v, imageOptions);
                    NCHECK(image)

                    SharedRef<Texture> texture = options.RenderDevice->CreateTexture(image, textureConstructOptions);
                    NCHECK(texture);

                    texturesMapping.insert({v, texture});
                    material.DiffuseTexture = texturesMapping.at(v);
                }
            }

            if (m.specular_texname.length() > 0)
            {
                std::string imagePath = mtlPathDir->GetFilePath() + m.specular_texname;

                if (!texturesMapping.contains(imagePath) && toSubmit)
                {
                    SharedRef<ImageAsset> image = assets.Load<ImageAsset>(imagePath, imageOptions);
                    NCHECK(image)

                    SharedRef<Texture> texture = options.RenderDevice->CreateTexture(image, textureConstructOptions);
                    NCHECK(texture);

                    texturesMapping.insert({imagePath, texture});
                    material.SpecularTexture = texturesMapping.at(imagePath);
                }
            }

            inMaterials.push_back(material);
        }

        // Loop over shapes
        for (const tinyobj::shape_t& shape: shapes)
        {
            const tinyobj::mesh_t& mesh = shape.mesh;

            std::vector<Vertex> vertices;
            std::vector<VIndice> indices;
            std::unordered_set<UInt> mat_ids;
            std::vector<Material> mats;

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

                Material inMaterial = inMaterials.at(m);
                inMaterial.Id = UInt(m);
                if (!mat_ids.contains(inMaterial.Id))
                {
                    mat_ids.emplace(inMaterial.Id);
                    mats.push_back(inMaterial);
                }
            }

            Mesh ownMesh(std::move(vertices),
                         std::move(indices),
                         std::move(mats));

            if (toSubmit)
            {
                RenderCommandSubmitMesh(options.RenderDevice, ownMesh);
            }

            meshes.push_back(std::move(ownMesh));
        }


        NP_INFO(TOLModelLoader::Load, "Finish to load the model from '{}'", path.GetFilePath());

        return TRes(TRes::kValTag, Model(meshes));
    }
}// namespace Nenuphar