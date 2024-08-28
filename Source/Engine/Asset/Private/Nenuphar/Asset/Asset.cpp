#include "Nenuphar/Asset/Asset.hpp"
#include "Nenuphar/Core/IO/Path.hpp"


namespace Nenuphar
{

    static const char* AssetsFolderPathName = "/Assets";

    Path FromProject(std::string_view filepath)
    {
        return Path(NP_PROJECT_DIR + std::string(filepath));
    }

    Path FromAssets(std::string_view filepath)
    {
        return FromProject(AssetsFolderPathName + std::string(filepath));
    }

}