#include <iostream>

#include "ApplicationCore/ApplicationCore.hpp"
#include "Core/Core.hpp"


int main(int argc, char** argv)
{
    System system = CreateSystem();
    ApplicationCore applicationCore;

    applicationCore.Bind(system);

}


void ApplicationCore::Bind(System& bind)
{
    std::cout << "Binding a system...";
}
