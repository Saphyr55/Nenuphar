#include "Nenuphar/ApplicationCore/EntryPoint.hpp"
#include "Genesis/Genesis.hpp"

namespace Np = Nenuphar;

SharedRef<AppDelegate> Np::AppDelegateCreate()
{
    return MakeSharedRef<GenesisApp>();
}

int main(int argc, const char* argv[])
{
    return Np::NMain(argc, argv);
}
