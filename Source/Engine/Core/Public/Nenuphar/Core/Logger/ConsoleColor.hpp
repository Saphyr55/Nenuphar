#pragma once

#include "Nenuphar/Common.hpp"

namespace Nenuphar
{
    struct ConsoleColor
    {

        static String Reset();

        static String Red();

        static String Yellow();

        static String White();

        static String BGBlueFGWhite();

        static String BGGreenFGWhite();

        static String BGRedFGBlack();

        static String BGYellowFGBlack();

        static void SetConsoleColor(Word16 code, Word16 bg);
    };

}
