#include "Nenuphar/ApplicationCore/EntryPoint.hpp"
#include "StanfordBunny/StanfordBunnyApp.hpp"

namespace Np = Nenuphar;

SharedRef<AppDelegate> Np::AppDelegateCreate()
{
    return MakeSharedRef<StanfordBunnyApp>();
}

int main(int argc, const char* argv[])
{
    return Np::NMain(argc, argv);
}
