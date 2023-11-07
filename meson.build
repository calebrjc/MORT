project(
    'MORT',
    'c',
    default_options: [
        'buildtype=minsize',
        'b_lto=true',
        'cpp_rtti=false',
        'cpp_eh_=none',
        'default_library=static'
    ],
)

assert(meson.is_cross_build(), 'This project can only be built in a cross build environment.')

subdir('src/bsp_atmega328p')

sources = files(
    'src/main.c',
)

exe = executable(
    '@0@.bin'.format(meson.project_name()),
    include_directories: bsp_inc,
    sources: sources,
    link_with: bsp_lib,
)

objcopy = find_program('avr-objcopy')
avrdude = find_program('avrdude')

eep_output_file = '@0@.eep'.format(meson.project_name())
eep = custom_target(
    eep_output_file,
    input: exe,
    output: eep_output_file,
    command: [
        objcopy,
        '-O', 'ihex',
        '-j', '.eeprom',
        '--set-section-flags=.eeprom=alloc,load',
        '--no-change-warnings',
        '--change-section-lma', '.eeprom=0',
        '@INPUT@', '@OUTPUT@',
    ]
)

hex_output_file = '@0@.hex'.format(meson.project_name())
hex = custom_target(
    hex_output_file,
    input: exe,
    output: hex_output_file,
    command: [
        objcopy,
        '-O', 'ihex',
        '-R', '.eeprom',
        '@INPUT@', '@OUTPUT@',
    ],
    depends: eep,
)

run_target(
    'flash',
    command: [
        avrdude,
        '-v',
        '-p', 'atmega328p',
        '-c', 'arduino',
        '-P', 'COM4',
        '-b', '115200',
        '-D',
        '-Uflash:w:@0@:i'.format(hex.full_path())
    ],
    depends : hex,
)

run_target(
    'format',
    command: [
        'clang-format',
        '-i',
        sources,
        bsp_headers,
        bsp_sources,
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
        '-I', '../src/bsp_atmega328p/include',
        '-I', '../src/bsp_atmega328p/external/printf', # Hacky. I'll try to fix this later.
        sources,
        bsp_headers,
        bsp_sources,
    ],
    depends: hex,
)
