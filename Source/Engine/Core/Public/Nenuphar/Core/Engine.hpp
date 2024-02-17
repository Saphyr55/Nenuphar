#pragma once
#include <memory>


namespace Nenuphar
{

class Engine
{

public:
    static std::unique_ptr<Engine> Create();



};

}
