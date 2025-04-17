#pragma once

#define MORT_UNUSED(__x) ((void)(__x))

#ifdef __GNUC__
#define MORT_LIKELY(__x)   __builtin_expect(!!(__x), 1)
#define MORT_UNLIKELY(__x) __builtin_expect(!!(__x), 0)
#else
#define MORT_LIKELY(__x)   (__x)
#define MORT_UNLIKELY(__x) (__x)
#endif
