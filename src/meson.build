mort_inc = include_directories('.')

mort_src = files(
    'main.c',
    'hw.c',
)

mort_exe = executable(
    'mort.bin',
    include_directories: mort_inc,
    sources: mort_src,
    dependencies: [bsp_atmega328p_dep],
)

prgm_objcopy = find_program('avr-objcopy')

mort_eep_output_file = 'mort.eep'
mort_eep = custom_target(
    mort_eep_output_file,
    input: mort_exe,
    output: mort_eep_output_file,
    command: [
        prgm_objcopy,
        '-O', 'ihex',
        '-j', '.eeprom',
        '--set-section-flags=.eeprom=alloc,load',
        '--no-change-warnings',
        '--change-section-lma', '.eeprom=0',
        '@INPUT@', '@OUTPUT@',
    ],
)

mort_hex_output_file = 'mort.hex'
mort_hex = custom_target(
    mort_hex_output_file,
    input: mort_exe,
    output: mort_hex_output_file,
    command: [
        prgm_objcopy,
        '-O', 'ihex',
        '-R', '.eeprom',
        '@INPUT@', '@OUTPUT@',
    ],
    depends: mort_eep,
)
