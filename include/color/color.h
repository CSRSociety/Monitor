//
// Created by Administrator on 2022/10/27.
//

#ifndef COLOR_H_
#define COLOR_H_

#include <cstdint>

// basic ansi color, which found on Bing :)

#define ANSI_COLOR_RED     "\33[31m"
#define ANSI_COLOR_GREEN   "\33[32m"
#define ANSI_COLOR_YELLOW  "\33[33m"
#define ANSI_COLOR_BLUE    "\33[34m"
#define ANSI_COLOR_MAGENTA "\33[35m"
#define ANSI_COLOR_CYAN    "\33[36m"
#define ANSI_COLOR_RESET   "\33[0m"

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
