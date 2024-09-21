#include "Nenuphar/Rendering/Mesh.hpp"

namespace Nenuphar
{

    MeshStorage MeshStorage::s_mainStorage;

    MeshStorage::TStorage& MeshStorage::GetGlobalStorage()
    {
        return MeshStorage::s_mainStorage.m_storage;
    }

} // namespace Nenuphar