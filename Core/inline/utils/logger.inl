#pragma once

#include "utils/logger.hpp"

#include <utility>

#include "utils/utils.hpp"

BEGIN_XNOR_CORE

template <Formattable... Args>
void Logger::Log(const LogLevel level, const std::string& format, Args&&... args)
{
    if (level < minimumConsoleLevel && level < minimumFileLevel)
        return;

    m_Lines.Push(LogEntry(std::vformat(format, std::make_format_args(args...)), level));
    m_CondVar.notify_one();
}

template<Formattable ... Args>
void Logger::LogTempDebug(const std::string& format, const char_t* file, int32_t line, Args&&... args)
{
    if (LogLevel::TemporaryDebug < minimumConsoleLevel && LogLevel::TemporaryDebug < minimumFileLevel)
        return;
    
    m_Lines.Push(LogEntry(std::vformat(format, std::make_format_args(args...)), LogLevel::TemporaryDebug, file, line));
    m_CondVar.notify_one();
}

template <Formattable... Args>
void Logger::LogDebug(const std::string& format, Args&&... args)
{
    Logger::Log(LogLevel::Debug, format, std::forward<Args>(args)...);
}

template <Formattable... Args>
void Logger::LogInfo(const std::string& format, Args&&... args)
{
    Logger::Log(LogLevel::Info, format, std::forward<Args>(args)...);
}

template <Formattable... Args>
void Logger::LogWarning(const std::string& format, Args&&... args)
{
    Logger::Log(LogLevel::Warning, format, std::forward<Args>(args)...);
}

template <Formattable... Args>
void Logger::LogError(const std::string& format, Args&&... args)
{
    Logger::Log(LogLevel::Error, format, std::forward<Args>(args)...);
}

template <Formattable... Args>
void Logger::LogFatal(const std::string& format, Args&&... args)
{
    Logger::Log(LogLevel::Fatal, format, std::forward<Args>(args)...);
}

END_XNOR_CORE