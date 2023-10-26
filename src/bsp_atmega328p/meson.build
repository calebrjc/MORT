assert(meson.is_cross_build(), 'This project can only be built in a cross build environment.')

bsp_inc = include_directories('include')

bsp_headers = files(
    'include/bsp/hw_defs.h',
    'include/bsp/dsa/ring_buffer.h',
    'include/bsp/io/io.h',
    'include/bsp/usart/usart.h',
)

bsp_sources = files(
    'src/dsa/ring_buffer.c',
    'src/io/io.c',
    'src/usart/usart.c',
)

bsp_lib = library(
    'bsp_atmega328p',
    include_directories : bsp_inc,
    sources: bsp_sources,
    pic: false
)
