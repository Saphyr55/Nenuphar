#include "Nenuphar/Core/Windows.hpp"

#if NP_PLATFORM_WINDOWS
#include "Nenuphar/Core/IO/ConsoleColor.hpp"

namespace Nenuphar
{

    String ConsoleColor::Reset()
    {
        SetConsoleColor(7, 0);
        return "";
    }

    String ConsoleColor::Red()
    {
        SetConsoleColor(4, 0);
        return "";
    }

    String ConsoleColor::Yellow()
    {
        SetConsoleColor(6, 0);
        return "";
    }

    String ConsoleColor::White()
    {
        SetConsoleColor(7, 0);
        return "";
    }

    String ConsoleColor::BGBlueFGWhite()
    {
        int bg = BACKGROUND_BLUE | BACKGROUND_INTENSITY;
        int fg = 0 | FOREGROUND_INTENSITY;
        SetConsoleColor(fg, bg);
        return "";
    }

    String ConsoleColor::BGGreenFGWhite()
    {
        int bg = BACKGROUND_GREEN | BACKGROUND_INTENSITY;
        int fg = 0 | FOREGROUND_INTENSITY;
        SetConsoleColor(fg, bg);
        return "";
    }

    String ConsoleColor::BGRedFGBlack()
    {
        int bg = BACKGROUND_RED | BACKGROUND_INTENSITY;
        int fg = 0 | FOREGROUND_INTENSITY;
        SetConsoleColor(fg, bg);
        return "";
    }

    String ConsoleColor::BGYellowFGBlack()
    {
        int bg =
            BACKGROUND_RED |
            BACKGROUND_GREEN |
            BACKGROUND_INTENSITY;
        int fg = 0 | FOREGROUND_INTENSITY;

        SetConsoleColor(fg, bg);
        return "";
    }

    void ConsoleColor::SetConsoleColor(const Word16 code, const Word16 bg)
    {
        const HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(hConsole, code | bg);
    }

}

#endif
