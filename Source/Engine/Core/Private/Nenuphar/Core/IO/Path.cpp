#include "Nenuphar/Core/IO/Path.hpp"
#include "Nenuphar/Common/Type/Result.hpp"

#include <filesystem>
#include <fstream>
#include <string_view>

namespace fs = std::filesystem;

namespace Nenuphar
{

    Path::Path(std::string_view path)
        : m_path(path)
    {
    }

    bool Path::IsExists() const
    {
        return fs::exists(fs::path(m_path));
    }

    std::string Path::GetFilePath() const
    {
        return m_path;
    }

    Path::TRes ReadFileContent(const Path& path)
    {
        if (!path.IsExists())
        {
            return Path::TRes(Path::TRes::kErrTag, ErrorReadFileContent::NotExist);
        }

        std::ifstream ifs(path.GetFilePath());
        std::string content((std::istreambuf_iterator<char>(ifs)), std::istreambuf_iterator<char>());

        return Path::TRes(Path::TRes::kValTag, content);
    }
    
}