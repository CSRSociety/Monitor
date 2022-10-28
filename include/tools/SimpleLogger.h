//
// Created by Administrator on 2022/10/27.
//

#ifndef SIMPLELOGGER_H_
#define SIMPLELOGGER_H_

#include <string>
#include <iostream>

#include <utility>
#include "tools/Timetools.h"
#include "tools/color.h"

using std::string;

/**
 *
 */
class SimpleLogger {
public:
    // output level
    enum class OutputLevel {
        FATAL,
        ERROR,
        WARNING,
        INFO,
        FINE
    };

    using           LogLevel = OutputLevel;

    void            fatal(const string& message);
    void            error(const string& message) noexcept ;
    void            warning(const string& message) noexcept ;
    void            info(const string& message) noexcept ;
    void            fine(const string& message) noexcept ;

    void            output_log(const string& message, LogLevel log_level, FontColor color);

    SimpleLogger();
    explicit SimpleLogger(const string& name, OutputLevel level = OutputLevel::INFO);
    ~SimpleLogger();


private:
    string          logger_name;
    OutputLevel     output_level;

    void            set_font_color(FontColor color = FontColor::RESET);
    [[maybe_unused]]
    FontColor       get_font_color() noexcept ;

    void            set_logger_name(const string& name);
    void            set_logger_name(string&& name);
    string          get_logger_name() ;
};

void SimpleLogger::set_logger_name(const string& name) {
    logger_name = name;
}

void SimpleLogger::set_logger_name(string&& name) {
    logger_name = std::move(std::forward<string&&>(name));
}

string SimpleLogger::get_logger_name() {
    return logger_name;
}

SimpleLogger::SimpleLogger() {
    logger_name = "a logger";
    output_level = OutputLevel::INFO;
}

SimpleLogger::SimpleLogger(const std::string &name, SimpleLogger::OutputLevel level) {
    logger_name = name;
    output_level = level;
}

void SimpleLogger::fatal(const std::string &message) {
    set_font_color(FontColor::RED);

}

void SimpleLogger::error(const string &message) noexcept {

}

void SimpleLogger::warning(const string &message) noexcept {

}

void SimpleLogger::info(const string &message) noexcept {

}

void SimpleLogger::fine(const string &message) noexcept {

}

SimpleLogger::~SimpleLogger() {

}

void SimpleLogger::set_font_color(FontColor color) {
    std::cout << get_color_by_name(color);
}

void SimpleLogger::output_log(const string& message, LogLevel log_level, FontColor color) {
    set_font_color(color);
    std::cout << '[' << logger_name << ']' << Time::report_time()

}


#endif // SIMPLELOGGER_H_
