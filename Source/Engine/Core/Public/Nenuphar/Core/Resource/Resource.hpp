#pragma once


#include "Nenuphar/Common/Type/Type.hpp"

namespace Nenuphar
{

    class Path
    {
    public:
        static bool Exists(const Path& path);
        static String FilePathStr(const Path& path);
        static const char* FilePathData(const Path& path);

        explicit Path(StringView path);
        ~Path() = default;

    private:
        String m_path;
    };

    class ResourceManager
    {
    public:
        static String ReadStringContent(const Path& path);
        static Path FromProject(StringView path);
        static Path FromAssets(StringView path);
    };

}