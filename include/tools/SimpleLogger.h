//
// Created by Administrator on 2022/10/27.
//

#ifndef SIMPLELOGGER_H_
#define SIMPLELOGGER_H_

#include <string>
#include <iostream>
#include <sstream>
#include <charconv>

#include <utility>
#include "tools/Timetools.h"

#if (_WIN32)
#include "color/color_in_windows.h"
#undef ERROR
#elif (__linux__)
#include "color/color.h"
#else
#include "color/color.h"
#endif

using std::stringstream;
using std::string;

class LoggerManager;

/**
 * @brief A simple logger, use C++'s iostream tools. It's not a pretty good logger, but enough.
 * @brief 一个简单的日志类，使用了C++的标准输入输出流工具。它不是一个足够好的日志库，但足够了。
 * @example auto logger = SimpleLogger("A Logger");
 * @anchor CSR Society
 */
class SimpleLogger {
public:
    // output level
    enum class OutputLevel {
        FATAL = 0,
        ERROR = 1,
        WARNING = 2,
        INFO = 3,
        FINE = 4
    };

    // friend class: make class LoggerManager can access private member.
    // 友元：使得类 LoggerManager 能够访问 SimpleLogger 类的私有成员
    friend class LoggerManager;

    using           LogLevel = OutputLevel;

    // log functions
    // 各个日志函数
    void            fatal(const string& message) ;
    template<typename T>
    void            fatal(const T& message) ;
    template<typename T, typename... U>
    void            fatal(const T&, const U&...) ;

    void            error(const string& message) ;
    template<typename T>
    void            error(const T& message) ;
    template<typename T, typename ...U>
    void            error(const T& first, const U& ...args) ;

    void            warning(const string& message) ;
    template<typename T>
    void            warning(const T& message) ;
    template<typename T, typename ...U>
    void            warning(const T& first, const U& ...args) ;

    void            info(const string& message) ;
    template<typename T>
    void            info(const T& message) ;
    template<typename T, typename ...U>
    void            info(const T& first, const U& ...args) ;

    void            fine(const string& message) ;
    template<typename T>
    void            fine(const T& message) ;
    template<typename T, typename ...U>
    void            fine(const T& first, const U& ...args) ;



    void            output_log(const string& message, const string &log_level, FontColor color);
    void            output_log(const char* message, const string& log_level, FontColor color);

    SimpleLogger();
    // To prevent unnecessary translation
    // 为了避免不必要的隐式转换
    explicit SimpleLogger(const string& name, OutputLevel level = OutputLevel::INFO);
    ~SimpleLogger();

private:

    string          make_full_string(const char* str) ;
    template<typename T>
    string          make_full_string(const T& obj);
    string          make_full_string(stringstream& st);
    template<typename T>
    string          make_full_string(stringstream& st, const T& str);
    template<typename T, typename ...U>
    string          make_full_string(stringstream& st, const T& first, const U& ...args);

    string          logger_name;
    OutputLevel     output_level;

    void            set_logger_name(const string& name);
    string          get_logger_name() ;
};

void SimpleLogger::set_logger_name(const string& name) {
    logger_name = name;
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

SimpleLogger::~SimpleLogger() = default;

void SimpleLogger::fatal(const string& message) {
    if (this->output_level >= LogLevel::FATAL) {
        output_log(message, "fatal", FontColor::RED);
        cout << endl;
    }
}

template<typename T>
void SimpleLogger::fatal(const T& message) {
    if (this->output_level >= LogLevel::FATAL) {
        output_log(message, "fatal", FontColor::RED);
        cout << endl;
    }
}

template<typename T, typename... U>
void SimpleLogger::fatal(const T& first, const U&... args) {
    stringstream st;
    if (this->output_level >= LogLevel::FATAL) {
        output_log(make_full_string(st, first, args...), "fatal", FontColor::RED);
    }
}

void SimpleLogger::error(const string& message) {
    if (this->output_level >= LogLevel::ERROR) {
        output_log(message, "error", FontColor::MAGENTA);
        cout << endl;
    }
}

template<typename T>
void SimpleLogger::error(const T& message) {
    if (this->output_level >= LogLevel::ERROR) {
        output_log(message, "error", FontColor::MAGENTA);
        cout << endl;
    }
}

template<typename T, typename... U>
void SimpleLogger::error(const T& first, const U& ...args) {
    stringstream st;
    if (this->output_level >= LogLevel::ERROR) {
        output_log(make_full_string(st, first, args...), "error", FontColor::MAGENTA);
    }
}

void SimpleLogger::warning(const string& message) {
    if (this->output_level >= LogLevel::WARNING) {
        output_log(message, "warning", FontColor::YELLOW);
        cout << endl;
    }
}

template<typename T>
void SimpleLogger::warning(const T& message) {
    if (this->output_level >= LogLevel::WARNING) {
        output_log(message, "warning", FontColor::YELLOW);
        cout << endl;
    }
}

template<typename T, typename ...U>
void SimpleLogger::warning(const T& first, const U& ...args) {
    stringstream st;
    if (this->output_level >= LogLevel::WARNING) {
        output_log(make_full_string(st, first, args...), "warning", FontColor::YELLOW);
    }
}

void SimpleLogger::info(const string& message) {
    if (this->output_level >= LogLevel::INFO) {
        output_log(message, "info", FontColor::GREEN);
        cout << endl;
    }
}

template<typename T>
void SimpleLogger::info(const T& message) {
    if (this->output_level >= LogLevel::INFO) {
        output_log(message, "info", FontColor::GREEN);
        cout << endl;
    }
}

template<typename T, typename... U>
void SimpleLogger::info(const T &first, const U& ...args) {
    stringstream st;
    if (this->output_level >= LogLevel::INFO) {
        output_log(make_full_string(st, first, args...), "info", FontColor::GREEN);
    }
}

void SimpleLogger::fine(const string& message) {
    if (this->output_level >= LogLevel::FINE) {
        output_log(message, "fine", FontColor::BLUE);
        cout << endl;
    }
}

template<typename T>
void SimpleLogger::fine(const T& message) {
    if (this->output_level >= LogLevel::FINE) {
        output_log(message, "fine", FontColor::BLUE);
        cout << endl;
    }
}

template<typename T, typename... U>
void SimpleLogger::fine(const T &first, const U &... args) {
    stringstream st;
    if (this->output_level >= LogLevel::FINE) {
        output_log(make_full_string(st, first, args...), "fine", FontColor::BLUE);
    }
}

// 针对string类型的特化
void SimpleLogger::output_log(const string& message, const string& log_level, FontColor color) {
    stringstream st;
    st << Time::report_time() << '[' << logger_name << '/' << log_level
    << ']'  << ": " ;
    colored_output(st.str().c_str(), color);
}

void SimpleLogger::output_log(const char *message, const std::string &log_level, FontColor color) {
    stringstream st;
    st << Time::report_time() << '[' << logger_name << '/' << log_level
       << ']'  << ": " << message;
    colored_output(st.str().c_str(), color);
}

string SimpleLogger::make_full_string(const char* str) {
    return std::move(string(str));
}

template<typename T>
string SimpleLogger::make_full_string(const T &obj) {
    return std::move(string(to_string(obj)));
}

template<typename T>
string SimpleLogger::make_full_string(stringstream& st, const T &str) {
    st << str;
    return std::move(st.str());
}

template<typename T, typename... U>
string SimpleLogger::make_full_string(stringstream &st, const T &first, const U &... args) {
    st << first;
    return make_full_string(st, args...);
}

string SimpleLogger::make_full_string(stringstream &st) {
    return std::move(st.str());
}




#define ERROR 0
#endif // SIMPLELOGGER_H_
