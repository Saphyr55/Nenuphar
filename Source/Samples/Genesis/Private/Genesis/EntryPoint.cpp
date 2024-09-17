#include "Nenuphar/ApplicationCore/EntryPoint.hpp"
#include "Genesis/Genesis.hpp"


SharedRef<AppDelegate> Nenuphar::AppDelegateCreate()
{
    return MakeSharedRef<GenesisApp>();
}

int main(int argc, const char* argv[])
{
    return Nenuphar::NMain(argc, argv);
}
