#include "Nenuphar/Assets/Assets.hpp"

namespace Nenuphar
{

    String AssetsFolder::Path(StringView filepath)
    {
        return NP_PROJECT_DIR +
            String("/Assets") + 
            String(filepath);
    }

}

