#pragma once

#include "Nenuphar/Core/Resource/File.hpp"
#include "Texture.hpp"

#include <string>

namespace Nenuphar
{
    
    
    class TextureLoader
    {
    public:
        virtual TextureInformation Load(std::string_view filePath);
        
    };

}