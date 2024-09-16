#include "Nenuphar/Core/Logger/Logger.hpp"
#include "Nenuphar/Common/Type/Type.hpp"
#include "Nenuphar/Core/Debug.hpp"
#include "Nenuphar/Core/IO/ConsoleColor.hpp"

#include <chrono>
#include <iomanip>
#include <thread>

namespace Nenuphar
{

    SharedRef<Logger> GInstance;
    
    void DefineLogger(SharedRef<Logger> logger)
    {
        NCHECK(logger)
        GInstance = logger;
    }

    SharedRef<Logger> GetMainLogger()
    {
        NCHECK(GInstance)
        return GInstance;
    }

    String Logger::LevelString(const Level& level)
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

    String Logger::LevelColor(const Level& level)
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

    String Logger::LevelTextColor(const Level& level)
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

    String Logger::Details(const TimePoint<SysClock> time)
    {
        std::ostringstream oss;
        oss << std::this_thread::get_id();

        std::stringstream ss;
        const auto InTime = std::chrono::system_clock::to_time_t(time);
        ss << std::put_time(std::localtime(&InTime), "%Y-%m-%d %X");

        return fmt::format("{} {} {} ", ss.str(), oss.str(), name);
    }


}

