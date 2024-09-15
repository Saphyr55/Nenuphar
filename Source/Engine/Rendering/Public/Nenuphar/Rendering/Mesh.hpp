#pragma once


#include "Material.hpp"
#include "Nenuphar/Rendering/Texture.hpp"
#include "Nenuphar/Rendering/Vertex.hpp"

#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace Nenuphar
{

    using MeshId = std::size_t;


    struct Mesh
    {   
        std::vector<Vertex> Vertices;
        std::vector<VIndice> Indices;
        std::vector<Material> Materials;
    };


    // TODO: Use a sparse set and the pagination technique to have better perfomance.
    class MeshStorage
    {
    public:
        using TStorage = std::unordered_map<MeshId, Mesh>;
    
        static TStorage& GetGlobalStorage();

    private:
        TStorage m_storage;
        static MeshStorage s_mainStorage;
    };


} // namespace Nenuphar