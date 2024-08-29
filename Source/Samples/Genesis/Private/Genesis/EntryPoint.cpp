#include "Genesis/Genesis.hpp"
#include "Nenuphar/Asset/Asset.hpp"
#include "Nenuphar/Asset/AssetRegistry.hpp"
#include "Nenuphar/Common/Instanciate.hpp"
#include "Nenuphar/Common/Type/Type.hpp"
#include "Nenuphar/Core/Engine.hpp"
#include "Nenuphar/Core/Logger/Logger.hpp"
#include "Nenuphar/Model/ModelAsset.hpp"
#include "Nenuphar/Model/ModelLoader.hpp"
#include "Nenuphar/Rendering/TextureAsset.hpp"

namespace Np = Nenuphar;

int main(int argc, const char* argv[])
{
    SharedRef<Np::TextureAssetLoader> textureAssetLoader =
            MakeSharedRef<Np::TextureAssetLoader>();
    SharedRef<Np::ModelAssetLoader> modelAssetLoader =
            MakeSharedRef<Np::ModelAssetLoader>();

    Np::AssetRegistry::Instance()
            .AddLoader<Np::ModelAsset, Np::ModelAssetOptions>(modelAssetLoader);
    Np::AssetRegistry::Instance().AddLoader<Np::TextureAsset, Np::AssetOptions>(
            textureAssetLoader);

    GenesisApp app;

    NP_INFO(main, "Genesis application created.");

    app.OnInit();

    return Np::Engine::LoopRun([&app] {
        app.OnUpdate();
        app.OnRender();
    });
}
