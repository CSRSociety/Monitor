#ifndef SUBPROCESS_IN_WINDOWS
#define SUBPROCESS_IN_WINDOWS

#include <windows.h>

#include <cstdio>
#include <cstdint>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>



#include "tools/LoggerManager.h"

#define CREATE_PROCESS_FAIL 0



/*
 * BOOL CreateProcessA(
  [in, optional]      LPCSTR                lpApplicationName,
  [in, out, optional] LPSTR                 lpCommandLine,
  [in, optional]      LPSECURITY_ATTRIBUTES lpProcessAttributes,
  [in, optional]      LPSECURITY_ATTRIBUTES lpThreadAttributes,
  [in]                BOOL                  bInheritHandles,
  [in]                DWORD                 dwCreationFlags,
  [in, optional]      LPVOID                lpEnvironment,
  [in, optional]      LPCSTR                lpCurrentDirectory,
  [in]                LPSTARTUPINFOA        lpStartupInfo,
  [out]               LPPROCESS_INFORMATION lpProcessInformation
);
 */

/*
 * BOOL ReadFile(
  [in]                HANDLE       hFile,
  [out]               LPVOID       lpBuffer,
  [in]                DWORD        nNumberOfBytesToRead,
  [out, optional]     LPDWORD      lpNumberOfBytesRead,
  [in, out, optional] LPOVERLAPPED lpOverlapped
);
 */



class Popen {
public:
    SimpleLogger popen_logger;

    Popen(char* program, const char* mode = "r");

    
    bool        handle_close();


private:
    static constexpr uint32_t BUFFER_SIZE = 2048;

    pid_t       pid;
    HANDLE      child_stdin_rd;
    HANDLE      child_stdin_wr;
    HANDLE      child_stdout_rd;
    HANDLE      child_stdout_wr;

    HANDLE      input_file;

    pid_t       create_child_process(char* cmd);
    uint32_t    write_to_pipe(char* buffer, uint32_t size);
    uint32_t    read_from_file(char* buffer, uint32_t size);

    template<typename T>
    inline void zero_mem(T* obj);
};

Popen::Popen(char *program, const char *mode) {
    popen_logger = SimpleLogger("popen", LogLevel::FINE);
    popen_logger.fine("create a child process successfully!");

    char test[BUFFER_SIZE]{0};
    char result[BUFFER_SIZE]{0};



    pid = create_child_process(program);

    if (pid == CREATE_PROCESS_FAIL) {
        popen_logger.fatal(R"(Cant't create a new child process. Monitor is end.)");
        exit(EXIT_FAILURE);
    }

}

bool Popen::handle_close() {
    child_stdin_rd = nullptr;
    return true;
}

/**
 * @brief 创建子进程
 * 
 * @param cmd 
 */
pid_t Popen::create_child_process(char* cmd) {
    SECURITY_ATTRIBUTES saAttr;

    saAttr.nLength = sizeof(SECURITY_ATTRIBUTES);
    saAttr.bInheritHandle = TRUE;
    saAttr.lpSecurityDescriptor = NULL;

    // 产生一个用于 stdout 的管道
    if (!CreatePipe(&child_stdout_rd, &child_stdout_wr, &saAttr, 0)) {
        popen_logger.fatal("Can\'t create a pipe.");
        return CREATE_PROCESS_FAIL;
    }

    if (!SetHandleInformation(child_stdout_rd, HANDLE_FLAG_INHERIT, 0)) {
        popen_logger.fatal("Can\'t set stdout into inherit");
        return CREATE_PROCESS_FAIL;
    }

    if (!CreatePipe(&child_stdin_rd, &child_stdin_wr, &saAttr, 0)) {
        popen_logger.fatal("Can\'t create a pipe.");
        return CREATE_PROCESS_FAIL;
    }

    if (!SetHandleInformation(child_stdin_wr, HANDLE_FLAG_INHERIT, 0)) {
        popen_logger.fatal("Can\'t set stdin into inherit.");
        return CREATE_PROCESS_FAIL;
    }


    auto cmdline = (CHAR*)(cmd);
    PROCESS_INFORMATION process_info;
    STARTUPINFO startup_info;
    BOOL success = FALSE;

    zero_mem(&process_info);
    zero_mem(&startup_info);

    startup_info.cb = sizeof(STARTUPINFO);
    startup_info.hStdError = child_stdout_wr;
    startup_info.hStdInput = child_stdin_rd;
    startup_info.hStdOutput = child_stdout_wr;
    startup_info.dwFlags |= STARTF_USESTDHANDLES;

    // now create the child process.
    success = CreateProcessA(
            nullptr,
            cmdline,
            nullptr,
            nullptr,
            TRUE,
            0,
            nullptr,
            nullptr,
            &startup_info,
            &process_info
            );

    if (!success) {
        popen_logger.fatal("Can\'t create a new process");
        return CREATE_PROCESS_FAIL;
    }
    else {
        // Close handles to the child process and its primary thread.
        // Some applications might keep these handles to monitor the status
        // of the child process, for example.
        // 关闭子进程及其主线程的句柄。
        // 一些应用程序可能会保留这些句柄来监视子进程的状态，例如。


        CloseHandle(process_info.hProcess);
        CloseHandle(process_info.hThread);

        // Close handles to the stdin and stdout pipes no longer needed by the child process.
        // If they are not explicitly closed, there is no way to recognize that the child process has ended.

        CloseHandle(child_stdout_wr);
        CloseHandle(child_stdin_rd);
    }
    auto id = getpid();
    auto id_win = GetCurrentProcessId();

    popen_logger.info("Process is running in PID ", id, ".");
    popen_logger.info("Process is running in PID", id_win, "(win32api).");

    return id;
}

template<typename T>
void Popen::zero_mem(T* obj) {
    ZeroMemory(obj, sizeof(T));
}

/**
 * @brief Write data to child process throuh the pipe, if success, it will return the number of written
 * char; 
 * @brief 通过管道向子进程写入数据，成功则返回写入的字符数量，失败则返回0
 * 
 * @param buffer 字符缓冲区，存放要写的数据
 * @param size 最大写入的字符数
 * @return uint32_t 成功写入的字符数
 */
uint32_t Popen::write_to_pipe(char* buffer, uint32_t size) {
    DWORD written;
    BOOL success = FALSE;

    success = WriteFile(child_stdin_wr, buffer, static_cast<DWORD>(size), &written, nullptr);
    if (!success) {
        return 0;
    }
    return written;
}

uint32_t Popen::read_from_file(char *buffer, uint32_t size) {
    DWORD read, written;
    BOOL success = FALSE;

    success = ReadFile(child_stdout_rd, buffer, size, &read, nullptr);
    if (!success || read == 0) {
        return 0;
    }

    success = WriteFile(GetStdHandle(STD_OUTPUT_HANDLE), buffer, read, &written, nullptr);
    if (!success) {
        return 0;
    }

    // return the number of readed char.
    // 返回所读取的字符数
    return read;
}


#endif