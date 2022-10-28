//
// Created by Administrator on 2022/10/26.
//

#ifndef MONITORGROUP_H_
#define MONITORGROUP_H_

#include "ProgramMonitor.h"

using Group = array<ProgramMonitor, 4>;

class MonitorGroup {
public:
    Group       monitor_groups;
    jthread     runner;


    MonitorGroup() noexcept ;
    ~MonitorGroup() noexcept ;
};

#endif
