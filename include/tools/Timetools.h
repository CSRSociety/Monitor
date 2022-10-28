//
// Created by Administrator on 2022/10/27.
//

#ifndef TIMER_H_
#define TIMER_H_

#include <chrono>
#include <string>
#include <sstream>

using namespace std::chrono;

using std::chrono::seconds;

using SteadyTPoint = _V2::steady_clock::time_point;
using SystemTPoint = _V2::system_clock::time_point;

using std::string;

/** @brief a pure time tools class
 *
 */
class Time {
public:
    //
    Time() = delete ;
    ~Time() = delete ;

    Time(const Time&) = delete ;
    Time(Time&&) = delete ;

    Time&               operator=(const Time&) = delete ;
    Time&               operator=(Time&&) = delete ;

    static inline SystemTPoint
                        get_time();
    static inline SteadyTPoint
                        get_steady_time();

    static string       report_time();


};

SystemTPoint Time::get_time() {
    return std::chrono::_V2::system_clock::now();
}

SteadyTPoint Time::get_steady_time() {
    return std::chrono::_V2::steady_clock::now();
}

string Time::report_time() {
    auto time = get_time();
    auto tt = system_clock::to_time_t(time);
    auto tm = gmtime(&tt);

    std::stringstream st;
    st << "[" << tm->tm_hour + 8 << ":" << tm->tm_min << ":" << tm->tm_sec
                      << "]";

    return st.str();
}

#endif // TIMER_H_
