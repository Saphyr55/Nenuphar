#pragma once

#include "Nenuphar/Core/Resource/File.hpp"
#include "Nenuphar/Common/Type/Type.hpp"

namespace Nenuphar
{
    
    class Path
    {
    public:
        bool IsExists() const;
        String GetFilePath() const;
        
        explicit Path(StringView path);
        ~Path() = default;

    private:
        String m_path;
    };

    class ResourceManager
    {
    public:
        static Path FromProject(StringView path);
        static Path FromAssets(StringView path);
    };

    String ReadFileContent(const Path& path);

    String ReadFileContent(const File& path);

}