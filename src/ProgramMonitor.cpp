#include "ProgramMonitor.h"




ProgramMonitor::ProgramMonitor(const char *program, const char *path, seconds time, OutputMode mode)  {
    program_name = program;
    program_path = path;
    waiting_time = time;
    output_mode = mode;


    for (bool flag = false; flag != true; ) {
        int8_t id = rand() % MAX_MONITOR_COUNT;

        for (auto &i: IDs) {
            if (i.first == id && i.second == true) {
                continue;
            }
            else {
                monitor_id = id;

                i = move(pair(id, true));
                flag = true;
            }
        }
    }

    init_and_run();
}

ProgramMonitor::~ProgramMonitor() {
    
}

void ProgramMonitor::start_monitoring() {

}

void ProgramMonitor::init_and_run() {
    start_monitoring();
}



