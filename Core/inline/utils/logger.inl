#pragma once

#include "utils/logger.hpp"

#include <utility>

#include "utils/utils.hpp"

BEGIN_XNOR_CORE

template <Concepts::FormattableT... Args>
void Logger::Log(const LogLevel level, const std::string& format, Args&&... args)
{
    if (level < minimumConsoleLevel && level < minimumFileLevel)
        return;

    PushLog(std::make_shared<LogEntry>(std::vformat(format, std::make_format_args(args...)), level));
}

template <Concepts::FormattableT ... Args>
void Logger::LogTempDebug(const std::string& format, const char_t* file, const int32_t line, Args&&... args)
{
    if (LogLevel::TemporaryDebug < minimumConsoleLevel && LogLevel::TemporaryDebug < minimumFileLevel)
        return;

    PushLog(std::make_shared<LogEntry>(std::vformat(format, std::make_format_args(args...)), LogLevel::TemporaryDebug, file, line));
}

template <Concepts::FormattableT... Args>
void Logger::LogDebug(const std::string& format, Args&&... args)
{
    Logger::Log(LogLevel::Debug, format, args...);
}

template <Concepts::FormattableT... Args>
void Logger::LogInfo(const std::string& format, Args&&... args)
{
    Logger::Log(LogLevel::Info, format, args...);
}

template <Concepts::FormattableT... Args>
void Logger::LogWarning(const std::string& format, Args&&... args)
{
    Logger::Log(LogLevel::Warning, format, args...);
}

template <Concepts::FormattableT... Args>
void Logger::LogError(const std::string& format, Args&&... args)
{
    Logger::Log(LogLevel::Error, format, args...);
}

template <Concepts::FormattableT... Args>
void Logger::LogFatal(const std::string& format, Args&&... args)
{
    Logger::Log(LogLevel::Fatal, format, args...);
}

END_XNOR_CORE
