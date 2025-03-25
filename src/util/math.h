#pragma once

#define MORT_IS_EVEN(__x) (((__x) & 1) == 0)
#define MORT_IS_ODD(__x)  (((__x) & 1) == 1)
#define MORT_MAP(__x, __in_min, __in_max, __out_min, __out_max)                                    \
    ((__x - __in_min) * (__out_max - __out_min) / (__in_max - __in_min) + __out_min)
