project(
    'MORT',
    'c',
    default_options : [
        'buildtype=minsize',
        'b_lto=true',
        'cpp_rtti=false',
        'cpp_eh_=none',
    ],
)

assert(meson.is_cross_build(), 'This project can only be built in a cross build environment.')

# List source files here
headers = files(
    'src/bsp/io/io.h',
    'src/bsp/io/pins.h',
)

sources = files(
    'src/main.c',
    'src/bsp/io/io.c',
)

exe = executable('@0@.bin'.format(meson.project_name()), [headers, sources])

objcopy = find_program('avr-objcopy')
avrdude = find_program('avrdude')

eep_output_file = '@0@.eep'.format(meson.project_name())
eep = custom_target(
    eep_output_file,
    input : exe,
    output : eep_output_file,
    command : [
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
    input : exe,
    output : hex_output_file,
    command : [
        objcopy,
        '-O', 'ihex',
        '-R', '.eeprom',
        '@INPUT@', '@OUTPUT@',
    ],
    depends : eep,
)

run_target(
    'flash',
    command : [
        avrdude,
        '-v',
        '-p', 'atmega328p',
        '-c', 'arduino',
        '-P', 'COM3',
        '-b', '115200',
        '-D',
        '-Uflash:w:@0@:i'.format(hex.full_path())
    ],
    depends : hex,
)

run_target(
    'check',
    command : [
        'cppcheck',
        '--quiet',
        '--platform=avr8',
        '--enable=all',
        '--suppress=missingIncludeSystem',
        '--suppress=unusedFunction',
        '--suppress=unusedStructMember',
        '--suppress=unusedVariable',
        '--suppress=unmatchedSuppression',
        headers,
        sources,
    ],
    depends: hex,
)
