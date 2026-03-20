#ifndef COMMON_H_
#define COMMON_H_

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <stdarg.h>
#include <ctype.h>

// Reset
#define COLOR_RESET        "\033[0m"
// Styles
#define COLOR_BOLD         "\033[1m"
#define COLOR_DIM          "\033[2m"
#define COLOR_ITALIC       "\033[3m"
#define COLOR_UNDERLINE    "\033[4m"
#define COLOR_BLINK        "\033[5m"
#define COLOR_REVERSE      "\033[7m"
// Foreground colors
#define COLOR_BLACK        "\033[30m"
#define COLOR_RED          "\033[31m"
#define COLOR_GREEN        "\033[32m"
#define COLOR_YELLOW       "\033[33m"
#define COLOR_BLUE         "\033[34m"
#define COLOR_MAGENTA      "\033[35m"
#define COLOR_CYAN         "\033[36m"
#define COLOR_WHITE        "\033[37m"
// Bright foreground colors
#define COLOR_BRIGHT_BLACK   "\033[90m"
#define COLOR_BRIGHT_RED     "\033[91m"
#define COLOR_BRIGHT_GREEN   "\033[92m"
#define COLOR_BRIGHT_YELLOW  "\033[93m"
#define COLOR_BRIGHT_BLUE    "\033[94m"
#define COLOR_BRIGHT_MAGENTA "\033[95m"
#define COLOR_BRIGHT_CYAN    "\033[96m"
#define COLOR_BRIGHT_WHITE   "\033[97m"
// Background colors
#define COLOR_BG_BLACK     "\033[40m"
#define COLOR_BG_RED       "\033[41m"
#define COLOR_BG_GREEN     "\033[42m"
#define COLOR_BG_YELLOW    "\033[43m"
#define COLOR_BG_BLUE      "\033[44m"
#define COLOR_BG_MAGENTA   "\033[45m"
#define COLOR_BG_CYAN      "\033[46m"
#define COLOR_BG_WHITE     "\033[47m"
// Bright background colors
#define COLOR_BG_BRIGHT_BLACK   "\033[100m"
#define COLOR_BG_BRIGHT_RED     "\033[101m"
#define COLOR_BG_BRIGHT_GREEN   "\033[102m"
#define COLOR_BG_BRIGHT_YELLOW  "\033[103m"
#define COLOR_BG_BRIGHT_BLUE    "\033[104m"
#define COLOR_BG_BRIGHT_MAGENTA "\033[105m"
#define COLOR_BG_BRIGHT_CYAN    "\033[106m"
#define COLOR_BG_BRIGHT_WHITE   "\033[107m"

#define RUN_TIME_ERROR(msg, ...) do {                                                           \
    run_time_error(msg, ##__VA_ARGS__);                                                         \
    fprintf(stderr, "in file: \"%s\", function: \"%s\", line: %u\n" COLOR_RESET,                \
                        __FILE__,           __func__,   __LINE__);                              \
} while(0)

#define _(this, method, ...) (this->vt->method ? this->vt->method(this, ##__VA_ARGS__) : NULL)

#define ARRAY_SIZE(arr) (sizeof(arr) / sizeof(arr[0]))

void run_time_error(const char* msg, ...);

#endif // COMMON_H_