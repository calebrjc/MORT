assert(meson.is_cross_build(), 'This project can only be built in a cross build environment.')

# Include external dependencies
subdir('external')

bsp_inc = include_directories('include')

bsp_headers = files(
    'include/bsp/dsa/queue.h',
    'include/bsp/io/io.h',
    'include/bsp/usart/usart.h',
    'include/bsp/util/assert.h',
)

bsp_sources = files(
    'src/dsa/queue.c',
    'src/io/io.c',
    'src/usart/usart.c',
    'src/util/assert.c',
)

bsp_lib = library(
    'bsp_atmega328p',
    include_directories: [bsp_inc, printf_inc],
    sources: bsp_sources,
    link_with: [printf_lib],
    pic: false
)
