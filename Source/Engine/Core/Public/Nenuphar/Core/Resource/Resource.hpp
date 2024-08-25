#pragma once

#include "Nenuphar/Common/Type/Type.hpp"

namespace Nenuphar
{

    class Path;

    Path FromProject(StringView path);

    Path FromAssets(StringView path);
}