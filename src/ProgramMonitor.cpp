#include "ProgramMonitor.h"


ProgramMonitor::ProgramMonitor() = default ;

ProgramMonitor::ProgramMonitor(const char *program, const char *path, seconds time, OutputMode mode)  {
    program_name = program;
    program_path = path;
    waiting_time = time;
    output_mode = mode;

    init_and_run();
}

ProgramMonitor::~ProgramMonitor() {
    
}

void ProgramMonitor::start_monitoring() {
    auto fp = _popen("tasklist", "r");
}

void ProgramMonitor::init_and_run() {
    start_monitoring();
}



