//
// Created by Administrator on 2022/10/28.
//

#include "tools/LoggerManager.h"
#include "subprocess/fork_in_windows.h"



int32_t main() {
    auto logger = LoggerManager::get_logger("a logger!", LogLevel::FINE);
    logger.info("this is a info!");
    logger.fine("all is fine!");
    logger.error("onno!");
    logger.warning("nononnnono");
    logger.fatal("oops!!");



    char o[] = R"(U:\proj\monitor\a.exe)";
    cout << o;
    auto a = Popen(o);


}
