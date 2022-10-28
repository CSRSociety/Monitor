//
// Created by Administrator on 2022/10/27.
//

#ifndef COLOR_H_
#define COLOR_H_

#include <cstdint>

// basic ansi color, which found on Bing :)

#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_COLOR_RESET   "\x1b[0m"

static const char *colors[] = {
        ANSI_COLOR_RED,
        ANSI_COLOR_GREEN,
        ANSI_COLOR_YELLOW,
        ANSI_COLOR_BLUE,
        ANSI_COLOR_MAGENTA,
        ANSI_COLOR_CYAN,
        ANSI_COLOR_RESET
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

inline const char* get_color_by_name(FontColor color) {
    return colors[static_cast<int8_t>(color)];
}

#endif // COLOR_H_
