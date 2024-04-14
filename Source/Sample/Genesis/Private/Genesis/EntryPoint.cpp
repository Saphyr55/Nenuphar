#include "Genesis/Genesis.hpp"

using namespace Nenuphar;

int main(int argc, const char* argv[])
{
    GEngine->Initialize(argc, argv);

    Window window("Genesis Application", 1080, 720);

    auto& env = Env::New(window);
    Env::Init(env);

    return GEngine->Start([&] { Env::Render(env); });
}


