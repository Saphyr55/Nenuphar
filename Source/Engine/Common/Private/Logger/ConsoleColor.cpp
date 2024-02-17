#include "Dramatic/Common/Logger/ConsoleColor.hpp"

#ifdef _WIN32
    #include <Windows.h>
#endif

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
#ifdef _WIN32
        int bg = BACKGROUND_BLUE | BACKGROUND_INTENSITY;
        int fg = 0 | FOREGROUND_INTENSITY;
#else
        int bg = 0;
        int fg = 0;
#endif
        SetConsoleColor(fg, bg);
        return "";
    }

    String ConsoleColor::BGGreenFGWhite()
    {
#ifdef _WIN32
        int bg = BACKGROUND_GREEN | BACKGROUND_INTENSITY;
        int fg = 0 | FOREGROUND_INTENSITY;
#else
        int bg = 0;
        int fg = 0;
#endif
        SetConsoleColor(fg, bg);
        return "";
    }

    String ConsoleColor::BGRedFGBlack()
    {
#ifdef _WIN32
        int bg = BACKGROUND_RED | BACKGROUND_INTENSITY;
        int fg = 0 | FOREGROUND_INTENSITY;
#else
        int bg = 0;
        int fg = 0;
#endif
        SetConsoleColor(fg, bg);
        return "";
    }

    String ConsoleColor::BGYellowFGBlack()
    {
#ifdef _WIN32
        int bg =
            BACKGROUND_RED |
            BACKGROUND_GREEN |
            BACKGROUND_INTENSITY;
        int fg = 0 | FOREGROUND_INTENSITY;
#else
        int bg = 0;
        int fg = 0;
#endif
        SetConsoleColor(fg, bg);
        return "";
    }

    void ConsoleColor::SetConsoleColor(const Word16 code, const Word16 bg)
    {
#ifdef _WIN32
        const HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(hConsole, code | bg);
#endif
    }

} // namespace Dramatic
