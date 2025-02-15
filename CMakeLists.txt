cmake_minimum_required(VERSION 3.20.0)

find_package(Zephyr REQUIRED HINTS $ENV{ZEPHYR_BASE})

project(mort)

set(MORT_SOURCES
    src/main.c
    src/driver/led.c
    src/driver/nec.c
    src/hal/counter.c
    src/hal/gpio.c
    src/hal/detail/dt.c
    src/task/app.c
    src/util/debug.c)

target_include_directories(app PRIVATE src)
target_sources(app PRIVATE ${MORT_SOURCES})
