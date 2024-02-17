#pragma once

#include <chrono>
#include <format>
#include <iostream>

#include "Nenuphar/Logger/ConsoleColor.hpp"
#include "Nenuphar/Common/Type/Type.hpp"


namespace Nenuphar
{
    /**
     * \brief
     */
    class Logger
    {
    public:
        /**
         * Specifies the severity or level of detail of the log message.
        */
        enum class Level : UInt8
        {
            /**
             * \brief
             */
            Trace,

            /**
             * \brief
             */
            Debug,

            /**
             * \brief
             */
            Info,

            /**
             * \brief
             */
            Warning,

            /**
             * \brief
             */
            Error,

            /**
             * \brief
             */
            Critical,

        };

        /**
         * \brief
         * \return
         */
        static Logger& GetLogger();

        /**
         * \brief
         * \param level
         * \return
         */
        static String LevelString(Level level);

        /**
         * \brief
         * \param level
         * \return
         */
        static String LevelColor(Level level);

        /**
         * \brief
         * \param level
         * \return
         */
        static String LevelTextColor(Level level);

        /**
         * \brief
         * \param level
         * \param fmt
         * \param args
         */
        template<typename ...Args>
        void Log(Level level, StringView fmt, Args&&... args);

        /**
         * \brief
         * \tparam Args
         * \param fmt
         * \param args
         */
        template<typename ...Args>
        void Info(StringView fmt, Args&&... args);

        /**
         * \brief
         * \tparam Args
         * \param fmt
         * \param args
         */
        template<typename ...Args>
        void Warn(StringView fmt, Args&&... args);

        /**
         * \brief
         * \tparam Args
         * \param fmt
         * \param args
         */
        template<typename ...Args>
        void Trace(StringView fmt, Args&&... args);

        /**
         * \brief
         * \tparam Args
         * \param fmt
         * \param args
         */
        template<typename ...Args>
        void Debug(StringView fmt, Args&&... args);

        /**
         * \brief
         * \tparam Args
         * \param fmt
         * \param args
         */
        template<typename ...Args>
        void Error(StringView fmt, Args&&... args);

        /**
         * \brief
         * \tparam Args
         * \param fmt
         * \param args
         */
        template<typename ...Args>
        void Critical(StringView fmt, Args&&... args);

        /**
         * \brief
         */
        explicit Logger(StringView name);

    private:

        template<typename T>
        using TimePoint = std::chrono::time_point<T>;

        using SysClock = std::chrono::system_clock;

        /**
         * \brief
         * \param now
         * \return
         */
        String Details(TimePoint<SysClock> now = SysClock::now());

        /**
         * \brief
         */
        String name;

        /**
         * \brief
         */
        static Ptr<Logger> Instance;
    };


    template<typename ...Args>
    void Logger::Log(const Level level, StringView fmt, Args&&... args)
    {
        const String details = Details();
        const String levelStr = std::format(" {} ", LevelString(level));
        const String space = " ";
        auto vargs = std::make_format_args(args...);
        const auto content = std::vformat(fmt, vargs);

        std::cout
            << details
            << space
            << LevelColor(level)
            << levelStr
            << ConsoleColor::Reset()
            << space
            << LevelTextColor(level)
            << content
            << ConsoleColor::Reset()
            << std::endl;
    }


    template<typename ...Args>
    void Logger::Info(StringView fmt, Args&&... args)
    {
        Log(Level::Info, fmt, args...);
    }


    template<typename ...Args>
    void Logger::Warn(StringView fmt, Args&&... args)
    {
        Log(Level::Warning, fmt, args...);
    }


    template<typename ...Args>
    void Logger::Trace(StringView fmt, Args&&... args)
    {
        Log(Level::Trace, fmt, args...);
    }


    template<typename ...Args>
    void Logger::Debug(StringView fmt, Args&&... args)
    {
        Log(Level::Debug, fmt, args...);
    }


    template<typename ...Args>
    void Logger::Error(StringView fmt, Args&&... args)
    {
        Log(Level::Error, fmt, args...);
    }


    template<typename ...Args>
    void Logger::Critical(StringView fmt, Args&&... args)
    {
        Log(Level::Critical, fmt, args...);
    }



}


#define DRL_INFO(NAME, ...)     ::Dramatic::Logger::GetLogger().Info(__VA_ARGS__)
#define DRL_WARN(NAME, ...)     ::Dramatic::Logger::GetLogger().Warn(__VA_ARGS__)
#define DRL_TRACE(NAME, ...)    ::Dramatic::Logger::GetLogger().Trace(__VA_ARGS__)
#define DRL_DEBUG(NAME, ...)    ::Dramatic::Logger::GetLogger().Debug(__VA_ARGS__)
#define DRL_ERROR(NAME, ...)    ::Dramatic::Logger::GetLogger().Error(__VA_ARGS__)
#define DRL_CRITICAL(NAME, ...) ::Dramatic::Logger::GetLogger().Critical(__VA_ARGS__)
