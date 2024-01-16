project(
    'MORT',
    'c',
    default_options: [
        'buildtype=minsize',
        'b_lto=true',
        'b_staticpic=false',
        'cpp_rtti=false',
        'cpp_eh_=none',
        'default_library=static'
    ],
)

assert(meson.is_cross_build(), 'This project can only be built in a cross build environment.')

# bsp-atmega328p
add_global_arguments(
    '-DPRINTF_DISABLE_SUPPORT_LONG_LONG',
    '-DPRINTF_DISABLE_SUPPORT_PTRDIFF_T',
    '-DPRINTF_DISABLE_SUPPORT_FLOAT',
    '-DPRINTF_DISABLE_SUPPORT_EXPONENTIAL',
    language: 'c',
)

bsp_atmega328p_dep = dependency('bsp-atmega328p')

subdir('src')

prgm_avrdude = find_program('avrdude')

run_target(
    'flash',
    command: [
        prgm_avrdude,
        '-v',
        '-p', 'atmega328p',
        '-c', 'arduino',
        '-P', 'COM3',
        '-b', '115200',
        '-D',
        '-Uflash:w:@0@:i'.format(mort_hex.full_path())
    ],
    depends : mort_hex,
)

run_target(
    'format',
    command: [
        'clang-format',
        '-i',
        mort_src,
    ]
)

run_target(
    'check',
    command: [
        'cppcheck',
        '--quiet',
        '--platform=avr8',
        '--enable=all',
        '--suppress=missingIncludeSystem',
        '--suppress=unusedFunction',
        '--suppress=unusedStructMember',
        '--suppress=unusedVariable',
        '--suppress=unmatchedSuppression',
        mort_src,
    ],
    depends: mort_hex,
)
