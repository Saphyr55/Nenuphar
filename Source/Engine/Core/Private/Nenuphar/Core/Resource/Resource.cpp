#include "Nenuphar/Core/Resource/Resource.hpp"
#include "Nenuphar/Core/Logger/Logger.hpp"

#include <filesystem>
#include <fstream>

namespace fs = std::filesystem;

namespace Nenuphar
{

    static const char* AssetsFolderPathName = "/Assets";

    Path::Path(StringView path)
        : m_path(path)
    {
    }

    bool Path::IsExists() const
    {
        return fs::exists(fs::path(m_path));
    }

    String Path::GetFilePath() const
    {
        return m_path;
    }

    Path ResourceManager::FromAssets(StringView filepath)
    {
        return FromProject(AssetsFolderPathName + String(filepath));
    }

    Path ResourceManager::FromProject(StringView filepath)
    {

        return Path(NP_PROJECT_DIR +  String(filepath));
    }

    String ReadStringContent(const Path& path)
    {
        if (!path.IsExists())
        {
            NP_ERROR(ResourceManager::ReadStringContent, "The path '{}' doesn't exist.", path.GetFilePath());
            throw std::exception();
        }

        std::ifstream ifs(path.GetFilePath());
        std::string content((std::istreambuf_iterator<char>(ifs)), std::istreambuf_iterator<char>());

        return content;
    }

}