#pragma once

#include "Nenuphar/Common/Common.hpp"

namespace Nenuphar
{

    class ConsoleColor
    {
    public:
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
