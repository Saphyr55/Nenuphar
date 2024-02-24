#pragma once

#include "Nenuphar/EventSystem/EventBus.hpp"
#include "Nenuphar/EventSystem/WindowEventHandler.hpp"

#define NPDefineAddress(Name, Address) \
constexpr ::Nenuphar::Char Name[] = Address;

#define NPDefineAddressStr(Name, Address) \
const ::Nenuphar::String Name = Address;
