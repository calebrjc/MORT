#include "util/debug.h"

#include <libgen.h>

#include <zephyr/kernel.h>

#include "driver/led.h"
#include "util/debug.h"

#define __MORT_UPTIME_FORMAT     "[%02d:%02d:%02d,%03d]"
#define __MORT_UPTIME_STR_LEN    17

// TODO(Caleb): Allow color output to be toggled via build flags.
#define __MORT_LOG_COLOR_RESET   "\033[39m"
#define __MORT_LOG_COLOR_RED     "\033[91m"
#define __MORT_LOG_COLOR_GRAY    "\033[90m"
#define __MORT_LOG_COLOR_GREEN   "\033[92m"
#define __MORT_LOG_COLOR_MAGENTA "\033[95m"
#define __MORT_LOG_COLOR_YELLOW  "\033[93m"

// NOTE(Caleb): Hex dump format example:
// 0x0000  23 20 42 75 69 6c 64 20  2d 2d 2d 2d 2d 2d 2d 2d  |# Build --------|
#define __MORT_LOG_HEX_LINE_LEN  76

// -----------------------------------------------------------------------------

/// @brief Get the color representation of a log level.
/// @param[in] level The log level.
/// @return The color representation of the log level.
static const char *__mort_log_get_level_color(int level);

/// @brief Get the string representation of a log level.
/// @param[in] level The log level.
/// @return The string representation of the log level.
static const char *__mort_log_get_level_str(int level);

/// @brief Format the current uptime into a string.
/// @param[out] o_data The output buffer.
/// @param[in] size The output buffer size.
static void __mort_log_format_uptime(char *o_data, size_t size);

// -----------------------------------------------------------------------------

void __mort_log_impl(int level, char *file, int line, const char *format, ...)
{
    // TODO(Caleb): Handle log level filtering.

    const char *color     = __mort_log_get_level_color(level);
    const char *level_str = __mort_log_get_level_str(level);

    static char time_str[__MORT_UPTIME_STR_LEN];
    __mort_log_format_uptime(time_str, __MORT_UPTIME_STR_LEN);

    file = basename(file);

    const char *log_format_format = "%s%s %s %s:%d - %s%s\n";
    int         log_format_size   = snprintf(
        NULL,
        0,
        log_format_format,
        color,
        time_str,
        level_str,
        file,
        line,
        format,
        __MORT_LOG_COLOR_RESET);

    char log_format[log_format_size + 1];
    snprintf(
        log_format,
        log_format_size + 1,
        log_format_format,
        color,
        time_str,
        level_str,
        file,
        line,
        format,
        __MORT_LOG_COLOR_RESET);

    va_list args;
    va_start(args, format);
    vprintf(log_format, args);
    va_end(args);
}

void __mort_log_hex_impl(int level, char *file, int line, const void *data, size_t size)
{
    // TODO(Caleb): Handle log level filtering.

    const char *color     = __mort_log_get_level_color(level);
    const char *level_str = __mort_log_get_level_str(level);

    static char time_str[__MORT_UPTIME_STR_LEN];
    __mort_log_format_uptime(time_str, __MORT_UPTIME_STR_LEN);

    file = basename(file);

    const char *header_format = "%s%s %s %s:%d -";
    int header_size = snprintf(NULL, 0, header_format, color, time_str, level_str, file, line);

    char header[header_size + 1];
    snprintf(header, header_size + 1, header_format, color, time_str, level_str, file, line);

    for (size_t i = 0; i < size; i += 16)
    {
        char line[__MORT_LOG_HEX_LINE_LEN + 1];
        int  render_idx = 0;

        // Line header + address ---------------------------

        render_idx +=
            snprintf(line + render_idx, __MORT_LOG_HEX_LINE_LEN + 1 - render_idx, "0x%04X  ", i);

        // Hex bytes ---------------------------------------

        for (size_t j = 0; j < 16; j++)
        {
            if (i + j < size)
            {
                render_idx += snprintf(
                    line + render_idx,
                    __MORT_LOG_HEX_LINE_LEN + 1 - render_idx,
                    "%02X ",
                    ((const uint8_t *)data)[i + j]);
            }
            else
            {
                render_idx +=
                    snprintf(line + render_idx, __MORT_LOG_HEX_LINE_LEN + 1 - render_idx, "   ");
            }

            if (j == 7)
            {
                render_idx +=
                    snprintf(line + render_idx, __MORT_LOG_HEX_LINE_LEN + 1 - render_idx, " ");
            }
        }

        // ASCII representation ----------------------------

        render_idx += snprintf(line + render_idx, __MORT_LOG_HEX_LINE_LEN + 1 - render_idx, "|");

        for (size_t j = 0; j < 16; j++)
        {
            if (i + j < size)
            {
                char c = ((const char *)data)[i + j];
                if (c < 32 || c > 126)
                {
                    c = '.';
                }

                render_idx +=
                    snprintf(line + render_idx, __MORT_LOG_HEX_LINE_LEN + 1 - render_idx, "%c", c);
            }
        }

        render_idx += snprintf(line + render_idx, __MORT_LOG_HEX_LINE_LEN + 1 - render_idx, "|\n");

        printf("%s %s", header, line);
    }
}

static const char *__mort_log_get_level_color(int level)
{
    static const char *LEVEL_COLORS[] = {
        [__MORT_LOG_LEVEL_NOTIFY]  = __MORT_LOG_COLOR_MAGENTA,
        [__MORT_LOG_LEVEL_ERROR]   = __MORT_LOG_COLOR_RED,
        [__MORT_LOG_LEVEL_WARNING] = __MORT_LOG_COLOR_YELLOW,
        [__MORT_LOG_LEVEL_INFO]    = __MORT_LOG_COLOR_RESET,
        [__MORT_LOG_LEVEL_DEBUG]   = __MORT_LOG_COLOR_GRAY,
    };

    return LEVEL_COLORS[level];
}

static const char *__mort_log_get_level_str(int level)
{
    static const char *LEVEL_STRINGS[] = {
        [__MORT_LOG_LEVEL_NOTIFY]  = "NTF",
        [__MORT_LOG_LEVEL_ERROR]   = "ERR",
        [__MORT_LOG_LEVEL_WARNING] = "WRN",
        [__MORT_LOG_LEVEL_INFO]    = "INF",
        [__MORT_LOG_LEVEL_DEBUG]   = "DBG",
    };

    return LEVEL_STRINGS[level];
}

static void __mort_log_format_uptime(char *o_data, size_t size)
{
    uint32_t uptime = k_uptime_get();

    uint32_t hours = uptime / (1000 * 60 * 60);
    uptime -= hours * (1000 * 60 * 60);
    uint32_t minutes = uptime / (1000 * 60);
    uptime -= minutes * (1000 * 60);
    uint32_t seconds = uptime / 1000;
    uptime -= seconds * 1000;

    snprintf(o_data, size, __MORT_UPTIME_FORMAT, hours, minutes, seconds, uptime);
}

void __mort_on_assert_failed(void)
{
    while (1)
    {
        __mort_debug_led_toggle();
        k_msleep(750);
    }
}

void __mort_debug_led_set_state(int state)
{
    mort_led_set_state(MORT_LED_DEBUG, state);
}

void __mort_debug_led_toggle(void)
{
    mort_led_toggle(MORT_LED_DEBUG);
}
