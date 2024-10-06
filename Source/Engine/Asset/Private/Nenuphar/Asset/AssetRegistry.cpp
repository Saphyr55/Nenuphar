#include "Nenuphar/Asset/AssetRegistry.hpp"

namespace Nenuphar
{
    
    AssetRegistry& AssetRegistry::Instance()
    {
        static AssetRegistry GMainRegistry;
        return GMainRegistry;
    }

}