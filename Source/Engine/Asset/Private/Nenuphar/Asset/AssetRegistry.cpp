#include "Nenuphar/Asset/AssetRegistry.hpp"

namespace Nenuphar
{
    AssetRegistry AssetRegistry::s_mainRegistry;

    AssetRegistry& AssetRegistry::Instance()
    {
        return s_mainRegistry;
    }

}