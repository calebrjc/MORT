# printf
printf_inc = include_directories('printf')
printf_headers = files('printf/printf.h')
printf_sources = files('printf/printf.c')
printf_lib = library(
    'printf',
    include_directories : printf_inc,
    sources: printf_sources,
    c_args: [
        '-DPRINTF_DISABLE_SUPPORT_LONG_LONG',
        '-DPRINTF_DISABLE_SUPPORT_PTRDIFF_T',
        '-DPRINTF_DISABLE_SUPPORT_FLOAT',
        '-DPRINTF_DISABLE_SUPPORT_EXPONENTIAL',
    ],
    pic: false,
)
