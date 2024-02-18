#pragma once

#include <Nenuphar/ApplicationCore/EntryApplication.hpp>
#include <Nenuphar/ApplicationCore/Window.hpp>
#include <Nenuphar/Core.hpp>

using namespace Nenuphar;

struct GenesisApplication final : EntryApplication
{

    void Initialize() override;

    void Update(Float deltaTime) override;


};

