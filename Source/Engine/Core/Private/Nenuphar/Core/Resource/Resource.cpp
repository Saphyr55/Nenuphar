#include "Nenuphar/Core/Resource/Resource.hpp"
#include "Nenuphar/Core/Logger/Logger.hpp"

#include <filesystem>
#include <fstream>

namespace fs = std::filesystem;

namespace Nenuphar
{

    static const char* AssetsFolderPathName = "/Assets";

    bool Path::Exists(const Path& path)
    {
        return fs::exists(fs::path(FilePathStr(path)));
    }

    Path::Path(StringView path)
        : m_path(path)
    {

    }

    String Path::FilePathStr(const Path& path)
    {
        return path.m_path;
    }

    const char* Path::FilePathData(const Path& path)
    {
        return path.m_path.data();
    }

    Path ResourceManager::FromAssets(StringView filepath)
    {
        return FromProject(AssetsFolderPathName + String(filepath));
    }

    Path ResourceManager::FromProject(StringView filepath)
    {
        return Path(NP_PROJECT_DIR +  String(filepath));
    }

    String ResourceManager::ReadStringContent(const Path& path)
    {
        if (!Path::Exists(path))
        {
            NP_ERROR(ResourceManager::ReadStringContent, "{} doesn't exist.", Path::FilePathStr(path));
            throw std::exception();
        }

        std::ifstream ifs(Path::FilePathData(path));
        std::string content((std::istreambuf_iterator<char>(ifs)), std::istreambuf_iterator<char>());
        return content;
    }

}