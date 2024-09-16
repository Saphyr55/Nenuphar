#include "Genesis/Genesis.hpp"
#include "Nenuphar/ApplicationCore/EntryPoint.hpp"

SharedRef<AppDelegate> Nenuphar::CreateAppDelegate()
{
    return MakeSharedRef<GenesisApp>();
}

int main(int argc, const char* argv[])
{
    return Nenuphar::NMain(argc, argv);
}

