#pragma once

#include "Nenuphar/Common/Type/Result.hpp"

#include <string_view>

namespace Nenuphar
{

    enum class ErrorReadFileContent
    {
        NotExist
    };

    class Path
    {
    public:
        using TRes = Result<std::string, ErrorReadFileContent>;

    public:
        
        bool IsExists() const;
        std::string GetFilePath() const;

        explicit Path(std::string_view path);
        ~Path() = default;

    private:
        std::string m_path;
    };

    Path::TRes ReadFileContent(const Path& path);
}