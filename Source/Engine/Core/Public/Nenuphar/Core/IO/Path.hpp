#pragma once

#include "Nenuphar/Common/Type/Result.hpp"

#include <string_view>
#include <string>

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
        std::string GetExtenstion() const;
        bool IsExists() const;

        std::string GetFilePath() const;
        
    public:
        explicit Path(std::string_view path);
        ~Path() = default;

    private:
        std::string m_extension;
        std::string m_path;
    };

    Path::TRes ReadFileContent(const Path& path);

} // namespace Nenuphar
