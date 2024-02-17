#include "Dramatic/Common/Logger/Logger.hpp"

#include <chrono>
#include <thread>

namespace Nenuphar
{

    Ptr<Logger> Logger::Instance = std::make_unique<Logger>("Dramatic.Engine");

    Logger& Logger::GetLogger()
    {
        return *Instance;
    }

    String Logger::LevelString(const Level level)
    {
        switch (level)
        {
            case Level::Trace:
                return "T";
            case Level::Debug:
                return "D";
            case Level::Info:
                return "I";
            case Level::Warning:
                return "W";
            case Level::Error:
                return "E";
            case Level::Critical:
                return "C";
        }

        return "N";
    }

    String Logger::LevelColor(const Level level)
    {
        switch (level)
        {
            case Level::Trace:
                return ConsoleColor::BGRedFGBlack();
            case Level::Debug:
                return ConsoleColor::BGGreenFGWhite();
            case Level::Info:
                return ConsoleColor::BGBlueFGWhite();
            case Level::Warning:
                return ConsoleColor::BGYellowFGBlack();
            case Level::Error:
                return ConsoleColor::BGRedFGBlack();
            case Level::Critical:
                return ConsoleColor::BGRedFGBlack();
        }

        return ConsoleColor::Reset();
    }

    String Logger::LevelTextColor(const Level level)
    {
        switch (level)
        {
            case Level::Trace:
                return ConsoleColor::Red();
            case Level::Debug:
                return ConsoleColor::White();
            case Level::Info:
                return ConsoleColor::White();
            case Level::Warning:
                return ConsoleColor::Yellow();
            case Level::Error:
                return ConsoleColor::Red();
            case Level::Critical:
                return ConsoleColor::Red();
        }

        return ConsoleColor::Reset();
    }

    Logger::Logger(const StringView name)
        : name(name)
    {
    }

    String Logger::Details(const TimePoint<SysClock> now)
    {
        std::ostringstream ss;
        ss << std::this_thread::get_id();
        return std::format("{:%F %T} {} {} ", std::localtime(now), ss.str(), name);
    }


}

