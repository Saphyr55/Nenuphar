#pragma once

#include <chrono>
#include <iostream>

#include <fmt/core.h>

#include "Nenuphar/Core/Logger/ConsoleColor.hpp"
#include "Nenuphar/Common/Common.hpp"

namespace Nenuphar
{

    /**
     * @brief 
     * 
     */
    class Logger
    {
        template<typename T>
        using TimePoint = std::chrono::time_point<T>;

        using SysClock = std::chrono::system_clock;

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
         * @brief Get the Logger object
         * 
         * @return Logger& 
         */
        static Logger& GetLogger();

        /**
         * @brief 
         * 
         * @param level 
         * @return String 
         */
        static String LevelString(const Level& level);

        /**
         * @brief 
         * 
         * @param level 
         * @return String 
         */
        static String LevelColor(const Level& level);

        /**
         * @brief 
         * 
         * @param level 
         * @return String 
         */
        static String LevelTextColor(const Level& level);

        /**
         * @brief 
         * 
         * @tparam Args 
         * @param level 
         * @param fmt 
         * @param args 
         */
        template<typename ...Args>
        void Log(const Level& level, std::string_view fmt, Args&&... args);

        /**
         * @brief 
         * 
         * @tparam Args 
         * @param fmt 
         * @param args 
         */
        template<typename ...Args>
        void Info(std::string_view fmt, Args&&... args);

        /**
         * @brief 
         * 
         * @tparam Args 
         * @param fmt 
         * @param args 
         */
        template<typename ...Args>
        void Warn(std::string_view fmt, Args&&... args);

        /**
         * @brief 
         * 
         * @tparam Args 
         * @param fmt 
         * @param args 
         */
        template<typename ...Args>
        void Trace(std::string_view fmt, Args&&... args);

        /**
         * @brief 
         * 
         * @tparam Args 
         * @param fmt 
         * @param args 
         */
        template<typename ...Args>
        void Debug(std::string_view fmt, Args&&... args);

        /**
         * @brief 
         * 
         * @tparam Args 
         * @param fmt 
         * @param args 
         */
        template<typename ...Args>
        void Error(std::string_view fmt, Args&&... args);

        /**
         * @brief 
         * 
         * @tparam Args 
         * @param fmt 
         * @param args 
         */
        template<typename ...Args>
        void Critical(std::string_view fmt, Args&&... args);

        /**
         * @brief Construct a new Logger object
         * 
         * @param name 
         */
        explicit Logger(std::string_view name);

    private:

        /**
         * @brief 
         * 
         * @param now 
         * @return String 
         */
        String Details(TimePoint<SysClock> now = SysClock::now());
    
    private:
        /**  */
        String name;

        /**  */
        static Ptr<Logger> Instance;
    };


    template<typename ...Args>
    void Logger::Log(const Level& level, std::string_view fmt, Args&&... args)
    {
        std::string details = Details();
        std::string levelStr = fmt::format(" {} ", Logger::LevelString(level));
        std::string space = " ";
        auto vargs = fmt::make_format_args(args...);
        std::string content = fmt::vformat(fmt, vargs);

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
    void Logger::Info(std::string_view fmt, Args&&... args)
    {
        Log(Level::Info, fmt, args...);
    }


    template<typename ...Args>
    void Logger::Warn(std::string_view fmt, Args&&... args)
    {
        Log(Level::Warning, fmt, args...);
    }


    template<typename ...Args>
    void Logger::Trace(std::string_view fmt, Args&&... args)
    {
        Log(Level::Trace, fmt, args...);
    }


    template<typename ...Args>
    void Logger::Debug(std::string_view fmt, Args&&... args)
    {
        Log(Level::Debug, fmt, args...);
    }


    template<typename ...Args>
    void Logger::Error(std::string_view fmt, Args&&... args)
    {
        Log(Level::Error, fmt, args...);
    }


    template<typename ...Args>
    void Logger::Critical(std::string_view fmt, Args&&... args)
    {
        Log(Level::Critical, fmt, args...);
    }



}


#define NP_INFO(NAME, ...)      ::Nenuphar::Logger::GetLogger().Info(__VA_ARGS__)
#define NP_WARN(NAME, ...)      ::Nenuphar::Logger::GetLogger().Warn(__VA_ARGS__)
#define NP_TRACE(NAME, ...)     ::Nenuphar::Logger::GetLogger().Trace(__VA_ARGS__)
#define NP_DEBUG(NAME, ...)     ::Nenuphar::Logger::GetLogger().Debug(__VA_ARGS__)
#define NP_ERROR(NAME, ...)     ::Nenuphar::Logger::GetLogger().Error(__VA_ARGS__)
#define NP_CRITICAL(NAME, ...)  ::Nenuphar::Logger::GetLogger().Critical(__VA_ARGS__)
