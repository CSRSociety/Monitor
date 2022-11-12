//
// Created by Administrator on 2022/10/30.
//

#ifndef LOGGERMANAGER_H_
#define LOGGERMANAGER_H_

#include "SimpleLogger.h"

class LoggerManager {
public:
    using LogLevel = SimpleLogger::LogLevel;

    LoggerManager() = default ;
    ~LoggerManager() = default ;
    static SimpleLogger get_logger(const char* name);
    static SimpleLogger get_logger(const char* name, LogLevel level);
    static SimpleLogger get_logger(const string& name);
    static SimpleLogger get_logger(const string& name, LogLevel level);
};

using LogLevel = LoggerManager::LogLevel;

SimpleLogger LoggerManager::get_logger(const char *name) {
    return SimpleLogger(name);
}

SimpleLogger LoggerManager::get_logger(const char *name, LoggerManager::LogLevel level) {
    return SimpleLogger(name, level);
}

SimpleLogger LoggerManager::get_logger(const std::string &name) {
    return SimpleLogger(name);
}

SimpleLogger LoggerManager::get_logger(const std::string &name, LoggerManager::LogLevel level) {
    return SimpleLogger(name, level);
}

#endif // LOGGERMANAGER_H_
