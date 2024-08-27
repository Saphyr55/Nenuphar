#pragma once

#ifndef NP_PLATFORM_WINDOWS
 #pragma error "Support only Windows."
#endif

#ifndef NP_PROJECT_DIR
 #pragma #error "The macro 'NP_PROJECT_DIR' is not define."
#endif

#include "Nenuphar/Core/Logger/Logger.hpp"
#include "Nenuphar/Core/Engine.hpp"
