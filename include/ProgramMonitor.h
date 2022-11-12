#ifndef PROGRAM_MONITOR_H_
#define PROGRAM_MONITOR_H_

#include <stdio.h>
#include <iostream>





#include <array>
#include <vector>
#include <random>

#include <thread>
#include <mutex>

#include <stdexcept>
#include <utility>

#include "tools/Timetools.h"

#include "subprocess/fork_in_windows.h"


using namespace std::chrono;


using std::mutex;
using std::lock_guard;
using std::jthread;
using std::array;
using std::vector;
using std::string;

using std::move;


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
    mutex           mtx;


    bool            is_null;

    string          program_name;
    string          program_path;

    seconds         waiting_time;
    OutputMode      output_mode;

    static void     start_monitoring();
    void            init_and_run();


};


#endif