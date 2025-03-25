#pragma once

#include "util/compiler.h"
#include "util/stdinc.h"

// TODO(Caleb): Configure the debug system using build flags

// LOGGING ---------------------------------------------------------------------

#define __MORT_LOG_LEVEL_NOTIFY  0
#define __MORT_LOG_LEVEL_ERROR   1
#define __MORT_LOG_LEVEL_WARNING 2
#define __MORT_LOG_LEVEL_INFO    3
#define __MORT_LOG_LEVEL_DEBUG   4

void __mort_log_impl(int level, char *file, int line, const char *format, ...);
void __mort_log_hex_impl(int level, char *file, int line, const void *data, size_t size);

#define __MORT_LOG_IMPL(__level, __fmt, ...)                                                       \
    __mort_log_impl(__level, __FILE__, __LINE__, __fmt, ##__VA_ARGS__)

#define __MORT_LOG_COND_IMPL(__cond, __level, __fmt, ...)                                          \
    do                                                                                             \
    {                                                                                              \
        if (!!(__cond))                                                                            \
        {                                                                                          \
            __MORT_LOG_IMPL(__level, __fmt, ##__VA_ARGS__);                                        \
        }                                                                                          \
    } while (0)

#define __MORT_LOG_HEX_IMPL(__level, __data, __size)                                               \
    __mort_log_hex_impl(__level, __FILE__, __LINE__, __data, __size)

#define MORT_LOGN(__fmt, ...) __MORT_LOG_IMPL(__MORT_LOG_LEVEL_NOTIFY, __fmt, ##__VA_ARGS__)
#define MORT_LOGE(__fmt, ...) __MORT_LOG_IMPL(__MORT_LOG_LEVEL_ERROR, __fmt, ##__VA_ARGS__)
#define MORT_LOGW(__fmt, ...) __MORT_LOG_IMPL(__MORT_LOG_LEVEL_WARNING, __fmt, ##__VA_ARGS__)
#define MORT_LOGI(__fmt, ...) __MORT_LOG_IMPL(__MORT_LOG_LEVEL_INFO, __fmt, ##__VA_ARGS__)
#define MORT_LOGD(__fmt, ...) __MORT_LOG_IMPL(__MORT_LOG_LEVEL_DEBUG, __fmt, ##__VA_ARGS__)

#define MORT_LOGN_IF(__cond, __fmt, ...)                                                           \
    __MORT_LOG_COND_IMPL(__cond, __MORT_LOG_LEVEL_NOTIFY, __fmt, ##__VA_ARGS__)
#define MORT_LOGE_IF(__cond, __fmt, ...)                                                           \
    __MORT_LOG_COND_IMPL(__cond, __MORT_LOG_LEVEL_ERROR, __fmt, ##__VA_ARGS__)
#define MORT_LOGW_IF(__cond, __fmt, ...)                                                           \
    __MORT_LOG_COND_IMPL(__cond, __MORT_LOG_LEVEL_WARNING, __fmt, ##__VA_ARGS__)
#define MORT_LOGI_IF(__cond, __fmt, ...)                                                           \
    __MORT_LOG_COND_IMPL(__cond, __MORT_LOG_LEVEL_INFO, __fmt, ##__VA_ARGS__)
#define MORT_LOGD_IF(__cond, __fmt, ...)                                                           \
    __MORT_LOG_COND_IMPL(__cond, __MORT_LOG_LEVEL_DEBUG, __fmt, ##__VA_ARGS__)

#define MORT_LOGN_HEX(__data, __size)                                                              \
    __MORT_LOG_HEX_IMPL(__MORT_LOG_LEVEL_NOTIFY, (__data), (__size))
#define MORT_LOGE_HEX(__data, __size)                                                              \
    __MORT_LOG_HEX_IMPL(__MORT_LOG_LEVEL_ERROR, (__data), (__size))
#define MORT_LOGW_HEX(__data, __size)                                                              \
    __MORT_LOG_HEX_IMPL(__MORT_LOG_LEVEL_WARNING, (__data), (__size))
#define MORT_LOGI_HEX(__data, __size) __MORT_LOG_HEX_IMPL(__MORT_LOG_LEVEL_INFO, (__data), (__size))
#define MORT_LOGD_HEX(__data, __size)                                                              \
    __MORT_LOG_HEX_IMPL(__MORT_LOG_LEVEL_DEBUG, (__data), (__size))

// ASSERTIONS ------------------------------------------------------------------

void __mort_on_assert_failed(void);

#define MORT_ASSERT(__cond)                                                                        \
    do                                                                                             \
    {                                                                                              \
        if (!MORT_UNLIKELY(__cond))                                                                \
        {                                                                                          \
            MORT_LOGE("Assertion failed: %s\n", #__cond);                                          \
            __mort_on_assert_failed();                                                             \
        }                                                                                          \
    } while (0)

#define MORT_ASSERT_MSG(__cond, __fmt, ...)                                                        \
    do                                                                                             \
    {                                                                                              \
        if (!MORT_UNLIKELY(__cond))                                                                \
        {                                                                                          \
            MORT_LOGE("Assertion failed: %s\n", #__cond);                                          \
            MORT_LOGE(__fmt, ##__VA_ARGS__);                                                       \
            __mort_on_assert_failed();                                                             \
        }                                                                                          \
    } while (0)

#define MORT_CRASH(__fmt, ...)                                                                     \
    do                                                                                             \
    {                                                                                              \
        MORT_LOGE("Crash forced: " __fmt, ##__VA_ARGS__);                                          \
        __mort_on_assert_failed();                                                                 \
    } while (0)

// CONDITIONAL RETURNS ---------------------------------------------------------

#define __MORT_RETURN_LOG_COND_IMPL(__cond, __level, __retval, __fmt, ...)                         \
    do                                                                                             \
    {                                                                                              \
        if (!!(__cond))                                                                            \
        {                                                                                          \
            __MORT_LOG_IMPL(__level, __fmt, ##__VA_ARGS__);                                        \
            return __retval;                                                                       \
        }                                                                                          \
    } while (0)

#define MORT_RETURN_IF(__cond, ...)                                                                \
    do                                                                                             \
    {                                                                                              \
        if (!!(__cond))                                                                            \
        {                                                                                          \
            return __VA_ARGS__;                                                                    \
        }                                                                                          \
    } while (0)

#define MORT_RETURN_LOGN_IF(__cond, __retval, __fmt, ...)                                          \
    __MORT_RETURN_LOG_COND_IMPL(__cond, __MORT_LOG_LEVEL_NOTIFY, __retval, __fmt, ##__VA_ARGS__)
#define MORT_RETURN_LOGE_IF(__cond, __retval, __fmt, ...)                                          \
    __MORT_RETURN_LOG_COND_IMPL(__cond, __MORT_LOG_LEVEL_ERROR, __retval, __fmt, ##__VA_ARGS__)
#define MORT_RETURN_LOGW_IF(__cond, __retval, __fmt, ...)                                          \
    __MORT_RETURN_LOG_COND_IMPL(__cond, __MORT_LOG_LEVEL_WARNING, __retval, __fmt, ##__VA_ARGS__)
#define MORT_RETURN_LOGI_IF(__cond, __retval, __fmt, ...)                                          \
    __MORT_RETURN_LOG_COND_IMPL(__cond, __MORT_LOG_LEVEL_INFO, __retval, __fmt, ##__VA_ARGS__)
#define MORT_RETURN_LOGD_IF(__cond, __retval, __fmt, ...)                                          \
    __MORT_RETURN_LOG_COND_IMPL(__cond, __MORT_LOG_LEVEL_DEBUG, __retval, __fmt, ##__VA_ARGS__)

// DEBUG LED -------------------------------------------------------------------

void __mort_debug_led_set_state(int state);
void __mort_debug_led_toggle(void);

#define MORT_DEBUG_LED_ON()     __mort_debug_led_set_state(1)
#define MORT_DEBUG_LED_OFF()    __mort_debug_led_set_state(0)
#define MORT_DEBUG_LED_TOGGLE() __mort_debug_led_toggle()
