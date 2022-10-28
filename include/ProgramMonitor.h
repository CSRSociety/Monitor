#ifndef PROGRAM_MONITOR_H_
#define PROGRAM_MONITOR_H_

#include <cstdio>
#include <iostream>

#include <array>
#include <vector>
#include <random>

#include <thread>
#include <mutex>

#include <stdexcept>
#include <utility>

#include "tools/Timetools.h"


using namespace std::chrono;

constexpr int8_t MAX_MONITOR_COUNT = 8;

using std::pair;
using std::mutex;
using std::lock_guard;
using std::jthread;
using std::array;
using std::vector;
using std::string;

using std::move;

using MonitorID = pair<int8_t, bool>;
using MonitorIDGroup = array<MonitorID , MAX_MONITOR_COUNT>;


class ProgramMonitor {
public:
    enum class OutputMode {
        All,
        INFO,
        LEAST
    };

    ProgramMonitor();
    ProgramMonitor(const char *program, const char *path , seconds time = 30s, OutputMode mode = OutputMode::INFO) ;
    ~ProgramMonitor();

private:
    int8_t          monitor_id;
    mutex           mtx;
    static MonitorIDGroup
                    IDs;

    bool            is_null;

    string          script_name;
    string          script_path;
    string          program_name;
    string          program_path;
    int32_t         program_count;
    seconds         waiting_time;
    OutputMode      output_mode;

    bool            generate_script();
    static void     start_monitoring();
    void            init_and_run();


};


#endif