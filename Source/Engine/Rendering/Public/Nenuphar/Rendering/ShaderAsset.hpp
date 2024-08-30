#pragma once

#include "Nenuphar/Asset/Asset.hpp"
#include "Nenuphar/Asset/AssetLoader.hpp"
#include "Nenuphar/Common/Type/Type.hpp"
#include "Nenuphar/Rendering/Shader.hpp"

namespace Nenuphar
{

    struct ShaderAssetOptions : AssetOptions
    {
    };

    class ShaderAsset : public Asset
    {
    public:
        inline SharedRef<Shader> GetShaderProgram();

        ShaderAsset() = default;
        virtual ~ShaderAsset() override = default;

    private:
        SharedRef<Shader> m_program;
    };

    class ShaderAssetLoader : public AssetLoader<ShaderAsset, ShaderAssetOptions>
    {
    public:
        virtual SharedRef<ShaderAsset> Load(
                const Path& path,
                const ShaderAssetOptions& options) override;
        
        virtual void Unload(SharedRef<ShaderAsset> asset) override;

    private:
    };

    inline SharedRef<Shader> ShaderAsset::GetShaderProgram()
    {
        return m_program;
    }

}// namespace Nenuphar