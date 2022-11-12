//
// Created by Administrator on 2022/11/9.
//

#ifndef MONITOR_COLOR_IN_WINDOWS_H
#define MONITOR_COLOR_IN_WINDOWS_H

#include <cstdint>
#include <iostream>
#include <cstdlib>

#include <Windows.h>

using std::cout;
using std::endl;

#define WINDOWS_COLOR_RED       0x0c
#define WINDOWS_COLOR_GREEN     0x0a
#define WINDOWS_COLOR_YELLOW    0x0e
#define WINDOWS_COLOR_BLUE      0x0b
#define WINDOWS_COLOR_MAGENTA   0x0d
#define WINDOWS_COLOR_CYAN      0x08
#define WINDOWS_COLOR_RESET     0x07

static const int8_t colors[] = {
        WINDOWS_COLOR_RED,
        WINDOWS_COLOR_GREEN,
        WINDOWS_COLOR_YELLOW,
        WINDOWS_COLOR_BLUE,
        WINDOWS_COLOR_MAGENTA,
        WINDOWS_COLOR_CYAN,
        WINDOWS_COLOR_RESET
};

enum class FontColor {
    RED = 0,
    GREEN = 1,
    YELLOW = 2,
    BLUE = 3,
    MAGENTA = 4,
    CYAN = 5,
    RESET = 6
};

int8_t get_color_by_name(FontColor color);
void colored_output(const char* str, FontColor color);



int8_t get_color_by_name(FontColor color) {
    return colors[static_cast<int8_t>(color)];
}

void colored_output(const char* str, FontColor color) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), get_color_by_name(color));
    cout << str;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), WINDOWS_COLOR_RESET);
}

#endif //MONITOR_COLOR_IN_WINDOWS_H
